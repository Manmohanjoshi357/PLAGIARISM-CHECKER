#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <string>

/**
 * FileReader Class
 * Handles reading files from a directory
 * Supports TXT files natively, with placeholders for PDF/DOCX
 */
class FileReader {
private:
    std::string folderPath;

public:
    /**
     * Constructor
     * @param path Path to the folder containing assignment files
     */
    FileReader(const std::string& path);

    /**
     * Get all file names from the folder
     * @return Vector of file names
     */
    std::vector<std::string> getFileNames() const;

    /**
     * Read content from a TXT file
     * @param filename Name of the file to read
     * @return Content of the file as a string
     */
    std::string readTXT(const std::string& filename) const;

    /**
     * Read content from a PDF file (Placeholder - requires external library)
     * @param filename Name of the PDF file
     * @return Content of the file as a string
     * @note This is a placeholder. To implement, use libraries like:
     *       - poppler (for PDF parsing)
     *       - pdf2text utilities
     */
    std::string readPDF(const std::string& filename) const;

    /**
     * Read content from a DOCX file (Placeholder - requires external library)
     * @param filename Name of the DOCX file
     * @return Content of the file as a string
     * @note This is a placeholder. To implement, use libraries like:
     *       - libzip (for DOCX parsing)
     *       - docx2txt utilities
     */
    std::string readDOCX(const std::string& filename) const;

    /**
     * Read content from a file based on its extension
     * @param filename Name of the file
     * @return Content of the file as a string
     */
    std::string readFile(const std::string& filename) const;

    /**
     * Read content from a file using full path
     * @param filePath Full path to the file
     * @return Content of the file as a string
     */
    static std::string readFileByPath(const std::string& filePath);
};

#endif // FILEREADER_H
