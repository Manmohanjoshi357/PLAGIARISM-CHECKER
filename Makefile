# Makefile for Smart Assignment Plagiarism Checker
# Team: Manmohan Joshi (67), Ryan Jose (46), Krishna Baliyan (72)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = plagiarism_checker
SOURCES = main.cpp FileReader.cpp TextCleaner.cpp FeatureExtractor.cpp SimilarityChecker.cpp ReportWriter.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Windows specific settings
ifeq ($(OS),Windows_NT)
    TARGET = plagiarism_checker.exe
    CXXFLAGS += -static-libgcc -static-libstdc++
endif

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
ifeq ($(OS),Windows_NT)
	del /Q $(OBJECTS) $(TARGET) 2>nul
endif

# Run the program with default settings
run: $(TARGET)
	./$(TARGET)
ifeq ($(OS),Windows_NT)
	$(TARGET)
endif

# Phony targets
.PHONY: all clean run

