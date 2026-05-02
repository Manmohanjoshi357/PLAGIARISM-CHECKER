#include "SimilarityChecker.h"
#include <cmath>
#include <algorithm>

SimilarityChecker::SimilarityChecker(const std::vector<std::map<std::string, double>>& vectors,
                                     const std::vector<std::string>& names)
    : tfidfVectors(vectors), documentNames(names) {
}

double SimilarityChecker::dotProduct(const std::map<std::string, double>& vec1,
                                     const std::map<std::string, double>& vec2) const {
    double result = 0.0;

    // Iterate through the smaller vector for efficiency
    const auto& smaller = (vec1.size() < vec2.size()) ? vec1 : vec2;
    const auto& larger = (vec1.size() < vec2.size()) ? vec2 : vec1;

    for (const auto& pair : smaller) {
        auto it = larger.find(pair.first);
        if (it != larger.end()) {
            result += pair.second * it->second;
        }
    }

    return result;
}

double SimilarityChecker::magnitude(const std::map<std::string, double>& vec) const {
    double sum = 0.0;
    for (const auto& pair : vec) {
        sum += pair.second * pair.second;
    }
    return std::sqrt(sum);
}

double SimilarityChecker::cosineSimilarity(int doc1Index, int doc2Index) const {
    if (doc1Index < 0 || doc1Index >= static_cast<int>(tfidfVectors.size()) ||
        doc2Index < 0 || doc2Index >= static_cast<int>(tfidfVectors.size())) {
        return 0.0;
    }

    if (doc1Index == doc2Index) {
        return 1.0; // Same document
    }

    const auto& vec1 = tfidfVectors[doc1Index];
    const auto& vec2 = tfidfVectors[doc2Index];

    double dot = dotProduct(vec1, vec2);
    double mag1 = magnitude(vec1);
    double mag2 = magnitude(vec2);

    // Avoid division by zero
    if (mag1 == 0.0 || mag2 == 0.0) {
        return 0.0;
    }

    return dot / (mag1 * mag2);
}

std::vector<std::tuple<std::string, std::string, double>> SimilarityChecker::compareAll() const {
    std::vector<std::tuple<std::string, std::string, double>> results;

    int numDocs = static_cast<int>(tfidfVectors.size());

    // Compare all pairs of documents (avoid duplicates and self-comparisons)
    for (int i = 0; i < numDocs; i++) {
        for (int j = i + 1; j < numDocs; j++) {
            double similarity = cosineSimilarity(i, j);
            std::string name1 = (i < static_cast<int>(documentNames.size())) ? documentNames[i] : "Document" + std::to_string(i);
            std::string name2 = (j < static_cast<int>(documentNames.size())) ? documentNames[j] : "Document" + std::to_string(j);
            
            results.push_back(std::make_tuple(name1, name2, similarity));
        }
    }

    return results;
}

