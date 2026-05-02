#include "FeatureExtractor.h"
#include <algorithm>
#include <cmath>
#include <set>

FeatureExtractor::FeatureExtractor(const std::vector<std::vector<std::string>>& docs) 
    : documents(docs) {
    buildVocabulary();
}

void FeatureExtractor::buildVocabulary() {
    std::set<std::string> vocabSet;

    // Collect all unique words from all documents
    for (const auto& doc : documents) {
        for (const auto& word : doc) {
            vocabSet.insert(word);
        }
    }

    // Convert set to vector
    vocabulary.assign(vocabSet.begin(), vocabSet.end());
}

std::map<std::string, double> FeatureExtractor::computeTF(const std::vector<std::string>& document) const {
    std::map<std::string, double> tf;
    
    if (document.empty()) {
        return tf;
    }

    // Count term frequencies
    std::map<std::string, int> termCount;
    for (const auto& term : document) {
        termCount[term]++;
    }

    // Compute TF: term frequency / total terms in document
    double totalTerms = static_cast<double>(document.size());
    for (const auto& pair : termCount) {
        tf[pair.first] = static_cast<double>(pair.second) / totalTerms;
    }

    return tf;
}

std::map<std::string, double> FeatureExtractor::computeIDF() const {
    std::map<std::string, double> idf;
    
    if (documents.empty()) {
        return idf;
    }

    double totalDocs = static_cast<double>(documents.size());

    // For each term in vocabulary, count in how many documents it appears
    for (const auto& term : vocabulary) {
        int docCount = 0;
        for (const auto& doc : documents) {
            if (std::find(doc.begin(), doc.end(), term) != doc.end()) {
                docCount++;
            }
        }

        // IDF = log(total_documents / documents_containing_term)
        if (docCount > 0) {
            idf[term] = std::log10(totalDocs / static_cast<double>(docCount));
        } else {
            idf[term] = 0.0;
        }
    }

    return idf;
}

void FeatureExtractor::computeTFIDF() {
    tfidfVectors.clear();
    
    if (documents.empty()) {
        return;
    }

    // Compute IDF for all terms
    std::map<std::string, double> idf = computeIDF();

    // Compute TF-IDF for each document
    for (const auto& doc : documents) {
        std::map<std::string, double> tf = computeTF(doc);
        std::map<std::string, double> tfidf;

        // TF-IDF = TF * IDF
        for (const auto& term : vocabulary) {
            double tfValue = (tf.find(term) != tf.end()) ? tf[term] : 0.0;
            double idfValue = idf[term];
            tfidf[term] = tfValue * idfValue;
        }

        tfidfVectors.push_back(tfidf);
    }
}

std::map<std::string, double> FeatureExtractor::getTFIDFVector(int docIndex) const {
    if (docIndex >= 0 && docIndex < static_cast<int>(tfidfVectors.size())) {
        return tfidfVectors[docIndex];
    }
    return std::map<std::string, double>();
}

std::vector<std::map<std::string, double>> FeatureExtractor::getAllTFIDFVectors() const {
    return tfidfVectors;
}

std::vector<std::string> FeatureExtractor::getVocabulary() const {
    return vocabulary;
}
