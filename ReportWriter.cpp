#include "ReportWriter.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iostream>

ReportWriter::ReportWriter(const std::string& path, double thresh) 
    : outputPath(path), threshold(thresh) {
}

void ReportWriter::setThreshold(double thresh) {
    threshold = thresh;
}

void ReportWriter::writeCSV(const std::vector<std::tuple<std::string, std::string, double>>& results) const {
    std::ofstream file(outputPath);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open output file: " << outputPath << std::endl;
        return;
    }

    // Write CSV header
    file << "Student Pair,Similarity Percentage,Plagiarized\n";

    // Write results
    for (const auto& result : results) {
        std::string student1 = std::get<0>(result);
        std::string student2 = std::get<1>(result);
        double similarity = std::get<2>(result);

        // Format student pair
        std::string pair = student1 + " vs " + student2;
        
        // Convert similarity (0.0-1.0) to percentage
        double percentage = similarity * 100.0;

        // Determine if plagiarized
        std::string plagiarized = (similarity > threshold) ? "Yes" : "No";

        // Write to CSV
        file << std::fixed << std::setprecision(2);
        file << "\"" << pair << "\"," << percentage << "%," << plagiarized << "\n";
    }

    file.close();
    std::cout << "Report written to: " << outputPath << std::endl;
}

