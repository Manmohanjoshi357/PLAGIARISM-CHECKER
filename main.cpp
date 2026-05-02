#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <tuple>
#include "FileReader.h"
#include "TextCleaner.h"
#include "FeatureExtractor.h"
#include "SimilarityChecker.h"
#include "ReportWriter.h"

/**
 * Main function - Plagiarism Checker Pipeline
 * 
 * This program:
 * 1. Reads assignment files (from folder or command line arguments)
 * 2. Preprocesses the text
 * 3. Computes TF-IDF vectors
 * 4. Calculates cosine similarity between documents
 * 5. Generates a CSV report
 * 
 * Usage:
 *   Mode 1: Read from folder
 *     ./plagiarism_checker [folder] [output] [threshold]
 *   
 *   Mode 2: Read specific files
 *     ./plagiarism_checker -f file1.txt file2.txt file3.txt [output] [threshold]
 */
int main(int argc, char* argv[]) {
    // Default values
    std::string outputFile = "plagiarism_report.csv";
    double threshold = 0.70; // 70% similarity threshold
    std::vector<std::string> filePaths;
    std::vector<std::string> documentNames;
    bool useFileMode = false;

    // Parse command line arguments
    if (argc > 1) {
        std::string firstArg = argv[1];
        
        // Check if using file mode (-f flag)
        if (firstArg == "-f" || firstArg == "--files") {
            useFileMode = true;
            // Collect all file paths (everything after -f until optional output/threshold)
            int fileCount = 0;
            for (int i = 2; i < argc; i++) {
                std::string arg = argv[i];
                // Simple check: if it ends with .txt, .pdf, .docx, it's a file
                // Otherwise, treat as output file or threshold
                if (arg.length() > 4 && 
                    (arg.substr(arg.length() - 4) == ".txt" ||
                     arg.substr(arg.length() - 4) == ".pdf" ||
                     (arg.length() > 5 && arg.substr(arg.length() - 5) == ".docx"))) {
                    filePaths.push_back(arg);
                    fileCount++;
                } else {
                    // Could be output file or threshold
                    // If it contains a dot and looks like a filename, it's output
                    if (arg.find('.') != std::string::npos && arg.find('/') == std::string::npos && arg.find('\\') == std::string::npos) {
                        outputFile = arg;
                    } else {
                        // Try to parse as threshold
                        try {
                            threshold = std::stod(arg);
                            if (threshold < 0.0 || threshold > 1.0) {
                                threshold = 0.70;
                            }
                        } catch (...) {
                            // Not a number, ignore
                        }
                    }
                }
            }
        } else {
            // Folder mode (legacy mode)
            std::string inputFolder = firstArg;
            if (argc > 2) {
                outputFile = argv[2];
            }
            if (argc > 3) {
                threshold = std::stod(argv[3]);
                if (threshold < 0.0 || threshold > 1.0) {
                    std::cerr << "Warning: Threshold should be between 0.0 and 1.0. Using default 0.70." << std::endl;
                    threshold = 0.70;
                }
            }

            // Read files from folder
            FileReader reader(inputFolder);
            std::vector<std::string> fileNames = reader.getFileNames();
            
            if (fileNames.empty()) {
                std::cerr << "Error: No supported files found in folder: " << inputFolder << std::endl;
                std::cerr << "Supported formats: .txt, .pdf, .docx" << std::endl;
                return 1;
            }

            // Convert folder-relative names to full paths
            for (const auto& name : fileNames) {
                filePaths.push_back(inputFolder + "/" + name);
                documentNames.push_back(name);
            }
        }
    } else {
        // No arguments - use default folder
        std::string inputFolder = "assignments";
        FileReader reader(inputFolder);
        std::vector<std::string> fileNames = reader.getFileNames();
        
        if (fileNames.empty()) {
            std::cerr << "Error: No supported files found in folder: " << inputFolder << std::endl;
            std::cerr << "Usage: ./plagiarism_checker -f file1.txt file2.txt [file3.txt ...]" << std::endl;
            std::cerr << "   OR: ./plagiarism_checker [folder] [output] [threshold]" << std::endl;
            return 1;
        }

        for (const auto& name : fileNames) {
            filePaths.push_back(inputFolder + "/" + name);
            documentNames.push_back(name);
        }
    }

    // If in file mode, extract document names from paths
    if (useFileMode && documentNames.empty()) {
        for (const auto& path : filePaths) {
            size_t lastSlash = path.find_last_of("/\\");
            std::string name = (lastSlash != std::string::npos) 
                             ? path.substr(lastSlash + 1) 
                             : path;
            documentNames.push_back(name);
        }
    }

    if (filePaths.empty()) {
        std::cerr << "Error: No files specified." << std::endl;
        std::cerr << "Usage: ./plagiarism_checker -f file1.txt file2.txt [file3.txt ...]" << std::endl;
        std::cerr << "   OR: ./plagiarism_checker [folder] [output] [threshold]" << std::endl;
        return 1;
    }

    std::cout << "=== Smart Assignment Plagiarism Checker ===" << std::endl;
    std::cout << "\nOutput file: " << outputFile << std::endl;
    std::cout << "Similarity threshold: " << (threshold * 100) << "%" << std::endl;
    std::cout << "\nStarting plagiarism check...\n" << std::endl;

    // Step 1: Display files to process
    std::cout << "[1/5] Reading files..." << std::endl;
    std::cout << "Found " << filePaths.size() << " file(s):" << std::endl;
    for (size_t i = 0; i < filePaths.size(); i++) {
        std::cout << "  - " << documentNames[i] << std::endl;
    }

    // Step 2: Read and preprocess text
    std::cout << "\n[2/5] Reading and preprocessing text..." << std::endl;
    TextCleaner cleaner;
    std::vector<std::vector<std::string>> processedDocuments;

    for (size_t i = 0; i < filePaths.size(); i++) {
        std::string content = FileReader::readFileByPath(filePaths[i]);
        
        if (content.empty()) {
            std::cerr << "Warning: Could not read file: " << filePaths[i] << std::endl;
            continue;
        }

        std::vector<std::string> tokens = cleaner.preprocess(content);
        processedDocuments.push_back(tokens);

        std::cout << "  Processed: " << documentNames[i] 
                  << " (" << tokens.size() << " tokens)" << std::endl;
    }

    if (processedDocuments.empty()) {
        std::cerr << "Error: No valid documents to process." << std::endl;
        return 1;
    }

    // Step 3: Compute TF-IDF vectors
    std::cout << "\n[3/5] Computing TF-IDF vectors..." << std::endl;
    FeatureExtractor extractor(processedDocuments);
    extractor.computeTFIDF();
    std::vector<std::map<std::string, double>> tfidfVectors = extractor.getAllTFIDFVectors();
    std::cout << "  Vocabulary size: " << extractor.getVocabulary().size() << " unique terms" << std::endl;
    std::cout << "  TF-IDF vectors computed for " << tfidfVectors.size() << " documents" << std::endl;

    // Step 4: Compute similarity
    std::cout << "\n[4/5] Computing document similarities..." << std::endl;
    SimilarityChecker checker(tfidfVectors, documentNames);
    std::vector<std::tuple<std::string, std::string, double>> results = checker.compareAll();
    std::cout << "  Compared " << results.size() << " document pair(s)" << std::endl;

    // Display similarity results
    std::cout << "\nSimilarity Results:" << std::endl;
    for (const auto& result : results) {
        std::string doc1 = std::get<0>(result);
        std::string doc2 = std::get<1>(result);
        double similarity = std::get<2>(result);
        std::string status = (similarity > threshold) ? " [PLAGIARIZED]" : "";
        
        std::cout << "  " << doc1 << " vs " << doc2 
                  << ": " << std::fixed << std::setprecision(2) 
                  << (similarity * 100) << "%" << status << std::endl;
    }

    // Step 5: Generate CSV report
    std::cout << "\n[5/5] Generating CSV report..." << std::endl;
    ReportWriter writer(outputFile, threshold);
    writer.writeCSV(results);

    std::cout << "\n=== Plagiarism check completed! ===" << std::endl;
    std::cout << "Report saved to: " << outputFile << std::endl;

    return 0;
}

