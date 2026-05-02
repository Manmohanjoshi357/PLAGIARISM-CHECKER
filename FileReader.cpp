#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dirent.h>
#endif

FileReader::FileReader(const std::string& path) : folderPath(path) {
    // Ensure folder path ends with a separator
    if (!folderPath.empty() && folderPath.back() != '/' && folderPath.back() != '\\') {
        folderPath += "/";
    }
}

std::vector<std::string> FileReader::getFileNames() const {
    std::vector<std::string> fileNames;

#ifdef _WIN32
    // Windows implementation
    std::string searchPath = folderPath + "*.*";
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                std::string fileName = findData.cFileName;
                // Filter for supported file types
                std::string ext = fileName.substr(fileName.find_last_of(".") + 1);
                std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
                if (ext == "txt" || ext == "pdf" || ext == "docx") {
                    fileNames.push_back(fileName);
                }
            }
        } while (FindNextFileA(hFind, &findData) != 0);
        FindClose(hFind);
    }
#else
    // Linux/Mac implementation using dirent
    #include <dirent.h>
    DIR* dir = opendir(folderPath.c_str());
    if (dir != nullptr) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            std::string fileName = entry->d_name;
            if (fileName != "." && fileName != "..") {
                std::string ext = fileName.substr(fileName.find_last_of(".") + 1);
                std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
                if (ext == "txt" || ext == "pdf" || ext == "docx") {
                    fileNames.push_back(fileName);
                }
            }
        }
        closedir(dir);
    }
#endif

    return fileNames;
}

std::string FileReader::readTXT(const std::string& filename) const {
    std::string filePath = folderPath + filename;
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string FileReader::readPDF(const std::string& filename) const {
    // Placeholder implementation
    // To implement PDF reading, you would need external libraries like:
    // - poppler (poppler-cpp)
    // - pdf2text command-line tool
    // - PDF parsing libraries
    
    std::cerr << "Warning: PDF reading not implemented. "
              << "File: " << filename << " cannot be read." << std::endl;
    return "";
}

std::string FileReader::readDOCX(const std::string& filename) const {
    // Placeholder implementation
    // To implement DOCX reading, you would need external libraries like:
    // - libzip (for extracting DOCX as ZIP)
    // - XML parsing libraries
    // - docx2txt utilities
    
    std::cerr << "Warning: DOCX reading not implemented. "
              << "File: " << filename << " cannot be read." << std::endl;
    return "";
}

std::string FileReader::readFile(const std::string& filename) const {
    // Determine file type from extension
    std::string ext = filename.substr(filename.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if (ext == "txt") {
        return readTXT(filename);
    } else if (ext == "pdf") {
        return readPDF(filename);
    } else if (ext == "docx") {
        return readDOCX(filename);
    } else {
        std::cerr << "Warning: Unsupported file type: " << ext << std::endl;
        return "";
    }
}

std::string FileReader::readFileByPath(const std::string& filePath) {
    // Determine file type from extension
    size_t lastDot = filePath.find_last_of(".");
    if (lastDot == std::string::npos) {
        std::cerr << "Warning: File has no extension: " << filePath << std::endl;
        return "";
    }

    std::string ext = filePath.substr(lastDot + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    // Read based on extension
    if (ext == "txt") {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    } else if (ext == "pdf") {
        std::cerr << "Warning: PDF reading not implemented. "
                  << "File: " << filePath << " cannot be read." << std::endl;
        return "";
    } else if (ext == "docx") {
        std::cerr << "Warning: DOCX reading not implemented. "
                  << "File: " << filePath << " cannot be read." << std::endl;
        return "";
    } else {
        std::cerr << "Warning: Unsupported file type: " << ext << std::endl;
        return "";
    }
}
