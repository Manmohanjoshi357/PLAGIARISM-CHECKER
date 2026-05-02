#ifndef TEXTCLEANER_H
#define TEXTCLEANER_H

#include <vector>
#include <string>
#include <unordered_set>

/**
 * TextCleaner Class
 * Handles text preprocessing and cleaning operations
 */
class TextCleaner {
private:
    // Common English stopwords
    std::unordered_set<std::string> stopWords;

    /**
     * Initialize the stopwords set
     */
    void initializeStopWords();

public:
    /**
     * Constructor
     */
    TextCleaner();

    /**
     * Convert string to lowercase
     * @param text Input text
     * @return Lowercase text
     */
    std::string toLower(const std::string& text) const;

    /**
     * Remove punctuation from text
     * @param text Input text
     * @return Text without punctuation
     */
    std::string removePunctuation(const std::string& text) const;

    /**
     * Remove stopwords from tokenized text
     * @param tokens Vector of tokens
     * @return Vector of tokens without stopwords
     */
    std::vector<std::string> removeStopWords(const std::vector<std::string>& tokens) const;

    /**
     * Tokenize text into words
     * @param text Input text
     * @return Vector of tokens (words)
     */
    std::vector<std::string> tokenize(const std::string& text) const;

    /**
     * Complete preprocessing pipeline
     * @param text Raw input text
     * @return Cleaned and tokenized words
     */
    std::vector<std::string> preprocess(const std::string& text) const;
};

#endif // TEXTCLEANER_H
