#ifndef SIMILARITYCHECKER_H
#define SIMILARITYCHECKER_H

#include <vector>
#include <string>
#include <map>

/**
 * SimilarityChecker Class
 * Handles document similarity computation using cosine similarity
 */
class SimilarityChecker {
private:
    // TF-IDF vectors for all documents
    std::vector<std::map<std::string, double>> tfidfVectors;
    
    // Document names
    std::vector<std::string> documentNames;

    /**
     * Compute dot product of two TF-IDF vectors
     * @param vec1 First TF-IDF vector
     * @param vec2 Second TF-IDF vector
     * @return Dot product
     */
    double dotProduct(const std::map<std::string, double>& vec1, 
                     const std::map<std::string, double>& vec2) const;

    /**
     * Compute magnitude (Euclidean norm) of a TF-IDF vector
     * @param vec TF-IDF vector
     * @return Magnitude
     */
    double magnitude(const std::map<std::string, double>& vec) const;

public:
    /**
     * Constructor
     * @param vectors TF-IDF vectors for all documents
     * @param names Names of the documents
     */
    SimilarityChecker(const std::vector<std::map<std::string, double>>& vectors,
                     const std::vector<std::string>& names);

    /**
     * Compute cosine similarity between two documents
     * @param doc1Index Index of first document
     * @param doc2Index Index of second document
     * @return Cosine similarity (0.0 to 1.0)
     */
    double cosineSimilarity(int doc1Index, int doc2Index) const;

    /**
     * Compare all document pairs and return similarity scores
     * @return Vector of pairs: (doc1, doc2, similarity)
     */
    std::vector<std::tuple<std::string, std::string, double>> compareAll() const;
};

#endif // SIMILARITYCHECKER_H

