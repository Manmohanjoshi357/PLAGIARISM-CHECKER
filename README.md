# Smart Assignment Plagiarism Checker

**Team Members:**
- Manmohan Joshi (67)
- Ryan Jose (46)
- Krishna Baliyan (72)

## Overview

This is a C++ application that detects plagiarism in student assignments by comparing document similarity using TF-IDF (Term Frequency-Inverse Document Frequency) vectors and cosine similarity.

## Features

- Reads multiple assignment files from a folder
- Supports TXT files (PDF and DOCX support available as placeholders)
- Text preprocessing (lowercase conversion, punctuation removal, stopword removal)
- TF-IDF vector computation for document representation
- Cosine similarity calculation between document pairs
- CSV report generation with similarity percentages and plagiarism flags

## Project Structure

```
.
├── FileReader.h          # Header for file reading operations
├── FileReader.cpp        # Implementation of file reading
├── TextCleaner.h         # Header for text preprocessing
├── TextCleaner.cpp       # Implementation of text cleaning
├── FeatureExtractor.h    # Header for TF-IDF computation
├── FeatureExtractor.cpp  # Implementation of feature extraction
├── SimilarityChecker.h   # Header for similarity computation
├── SimilarityChecker.cpp # Implementation of similarity checking
├── ReportWriter.h        # Header for CSV report generation
├── ReportWriter.cpp      # Implementation of report writing
├── main.cpp              # Main program entry point
├── assignments/          # Folder containing sample assignment files
│   ├── assignment1.txt
│   ├── assignment2.txt
│   └── assignment3.txt
│   ├── assignment4.txt
│   
└── README.md             # This file
```

## How It Works

1. **File Reading**: The program reads all supported files (TXT, PDF, DOCX) from a specified folder.

2. **Text Preprocessing**: 
   - Converts text to lowercase
   - Removes punctuation
   - Removes common stopwords
   - Tokenizes the text into words

3. **Feature Extraction**:
   - Computes Term Frequency (TF) for each word in each document
   - Computes Inverse Document Frequency (IDF) for all words
   - Creates TF-IDF vectors for each document

4. **Similarity Computation**:
   - Calculates cosine similarity between all pairs of documents
   - Similarity ranges from 0.0 (completely different) to 1.0 (identical)

5. **Report Generation**:
   - Creates a CSV file with:
     - Student/document pairs
     - Similarity percentage
     - Plagiarism flag (Yes/No based on threshold)

## Compilation

### Using g++ (Linux/Mac/Git Bash on Windows)

```bash
g++ -std=c++17 -o plagiarism_checker *.cpp
```

### Using Microsoft Visual C++ (Windows)

```bash
cl /EHsc /std:c++17 *.cpp /Fe:plagiarism_checker.exe
```

### Using MinGW (Windows)

```bash
g++ -std=c++17 -o plagiarism_checker.exe *.cpp
```

**Note**: For Windows, if you encounter issues with `std::filesystem`, you may need to use the directory listing implementation provided (which uses Windows API).

## Usage

### Basic Usage

```bash
./plagiarism_checker
```

This will:
- Read files from the `assignments` folder
- Generate a report named `plagiarism_report.csv`
- Use default threshold of 70%

### Custom Usage

```bash
./plagiarism_checker <input_folder> <output_file> <threshold>
```

**Parameters:**
- `input_folder`: Path to folder containing assignment files (default: `assignments`)
- `output_file`: Name of output CSV file (default: `plagiarism_report.csv`)
- `threshold`: Similarity threshold between 0.0 and 1.0 (default: 0.70)

**Example:**
```bash
./plagiarism_checker assignments report.csv 0.75
```

## Output Format

The CSV report contains three columns:

| Column | Description |
|--------|-------------|
| Student Pair | Names of the two documents being compared |
| Similarity Percentage | Similarity score as a percentage (0-100%) |
| Plagiarized | "Yes" if similarity > threshold, "No" otherwise |

**Example Output:**
```csv
Student Pair,Similarity Percentage,Plagiarized
"assignment1.txt vs assignment2.txt",85.23%,Yes
"assignment1.txt vs assignment3.txt",12.45%,No
"assignment2.txt vs assignment3.txt",15.67%,No
```

## Sample Test Files

The project includes three sample assignment files in the `assignments` folder:

- **assignment1.txt**: Original text about data structures
- **assignment2.txt**: Paraphrased version of assignment1 (high similarity expected)
- **assignment3.txt**: Different topic about OOP (low similarity expected)

## File Format Support

### Currently Supported
- **TXT files**: Fully implemented and tested

### Placeholder Support (Requires External Libraries)
- **PDF files**: Placeholder implementation. To add support, consider using:
  - poppler-cpp library
  - pdf2text command-line utilities
  
- **DOCX files**: Placeholder implementation. To add support, consider using:
  - libzip library (DOCX files are ZIP archives)
  - XML parsing libraries
  - docx2txt utilities

## Dependencies

- **C++17** or later
- **Standard Template Library (STL)**
- **No external libraries required** for TXT-only mode

## Algorithm Details

### TF-IDF (Term Frequency-Inverse Document Frequency)

- **Term Frequency (TF)**: `TF(term, doc) = (number of times term appears in doc) / (total terms in doc)`
- **Inverse Document Frequency (IDF)**: `IDF(term) = log10(total documents / documents containing term)`
- **TF-IDF**: `TF-IDF(term, doc) = TF(term, doc) × IDF(term)`

### Cosine Similarity

The cosine similarity between two TF-IDF vectors is calculated as:

```
similarity = (A · B) / (||A|| × ||B||)
```

Where:
- `A · B` is the dot product of vectors A and B
- `||A||` and `||B||` are the magnitudes (Euclidean norms) of the vectors

## Troubleshooting

### Issue: No files found
- Ensure the input folder path is correct
- Check that files have supported extensions (.txt, .pdf, .docx)
- Verify file permissions

### Issue: Compilation errors
- Ensure you're using C++17 or later
- On Windows, the code uses Windows API for directory listing
- On Linux/Mac, ensure filesystem library is available

### Issue: Empty output
- Check that files contain readable text
- Verify files are not empty
- Ensure files are in the correct format

## Future Enhancements

- [ ] Add PDF parsing support using poppler or similar libraries
- [ ] Add DOCX parsing support
- [ ] Implement n-gram analysis for better similarity detection
- [ ] Add support for multiple similarity metrics
- [ ] Create a GUI interface
- [ ] Add batch processing for multiple folders
- [ ] Implement database storage for historical comparisons

## License

This project is created for educational purposes.

## Contact

For questions or issues, please contact the development team.

