#include "TextCleaner.h"
#include <algorithm>
#include <sstream>
#include <cctype>
#include <iostream>

TextCleaner::TextCleaner() {
    initializeStopWords();
}

void TextCleaner::initializeStopWords() {
    // Common English stopwords
    std::vector<std::string> words = {
        "a", "an", "and", "are", "as", "at", "be", "by", "for", "from",
        "has", "he", "in", "is", "it", "its", "of", "on", "that", "the",
        "to", "was", "will", "with", "the", "this", "but", "they", "have",
        "had", "what", "said", "each", "which", "their", "time", "if",
        "up", "out", "many", "then", "them", "these", "so", "some", "her",
        "would", "make", "like", "into", "him", "has", "two", "more",
        "very", "after", "words", "long", "than", "first", "been", "call",
        "who", "oil", "sit", "now", "find", "down", "day", "did", "get",
        "come", "made", "may", "part"
    };

    for (const auto& word : words) {
        stopWords.insert(word);
    }
}

std::string TextCleaner::toLower(const std::string& text) const {
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string TextCleaner::removePunctuation(const std::string& text) const {
    std::string result;
    result.reserve(text.size());

    for (char c : text) {
        // Keep alphanumeric characters and spaces
        if (std::isalnum(c) || std::isspace(c)) {
            result += c;
        } else {
            // Replace punctuation with space
            result += ' ';
        }
    }

    return result;
}

std::vector<std::string> TextCleaner::removeStopWords(const std::vector<std::string>& tokens) const {
    std::vector<std::string> filtered;

    for (const auto& token : tokens) {
        if (stopWords.find(token) == stopWords.end() && !token.empty()) {
            filtered.push_back(token);
        }
    }

    return filtered;
}

std::vector<std::string> TextCleaner::tokenize(const std::string& text) const {
    std::vector<std::string> tokens;
    std::istringstream iss(text);
    std::string token;

    while (iss >> token) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    return tokens;
}

std::vector<std::string> TextCleaner::preprocess(const std::string& text) const {
    // Complete preprocessing pipeline
    std::string lowerText = toLower(text);
    std::string noPunct = removePunctuation(lowerText);
    std::vector<std::string> tokens = tokenize(noPunct);
    std::vector<std::string> cleaned = removeStopWords(tokens);
    
    return cleaned;
}
