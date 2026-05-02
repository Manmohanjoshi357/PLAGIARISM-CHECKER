#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#include <vector>
#include <string>
#include <map>
#include <unordered_map>

/**
 * FeatureExtractor Class
 * Handles TF-IDF vector computation for documents
 */
class FeatureExtractor {
private:
    // Document collection
    std::vector<std::vector<std::string>> documents;
    
    // Vocabulary (all unique words across all documents)
    std::vector<std::string> vocabulary;
    
    // TF-IDF vectors for each document
    std::vector<std::map<std::string, double>> tfidfVectors;

    /**
     * Build vocabulary from all documents
     */
    void buildVocabulary();

    /**
     * Compute Term Frequency for a document
     * @param document Tokenized document
     * @return Map of term -> frequency
     */
    std::map<std::string, double> computeTF(const std::vector<std::string>& document) const;

    /**
     * Compute Inverse Document Frequency for all terms
     * @return Map of term -> IDF value
     */
    std::map<std::string, double> computeIDF() const;

public:
    /**
     * Constructor
     * @param docs Vector of tokenized documents
     */
    FeatureExtractor(const std::vector<std::vector<std::string>>& docs);

    /**
     * Compute TF-IDF vectors for all documents
     */
    void computeTFIDF();

    /**
     * Get TF-IDF vector for a specific document
     * @param docIndex Index of the document
     * @return TF-IDF vector as a map
     */
    std::map<std::string, double> getTFIDFVector(int docIndex) const;

    /**
     * Get all TF-IDF vectors
     * @return Vector of TF-IDF maps
     */
    std::vector<std::map<std::string, double>> getAllTFIDFVectors() const;

    /**
     * Get vocabulary
     * @return Vector of all unique terms
     */
    std::vector<std::string> getVocabulary() const;
};

#endif // FEATUREEXTRACTOR_H
