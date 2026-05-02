#ifndef REPORTWRITER_H
#define REPORTWRITER_H

#include <vector>
#include <string>
#include <tuple>

/**
 * ReportWriter Class
 * Handles writing plagiarism check results to CSV file
 */
class ReportWriter {
private:
    std::string outputPath;
    double threshold;

public:
    /**
     * Constructor
     * @param path Output file path
     * @param thresh Similarity threshold for plagiarism flag (0.0 to 1.0)
     */
    ReportWriter(const std::string& path, double thresh = 0.7);

    /**
     * Write similarity results to CSV file
     * @param results Vector of tuples: (student1, student2, similarity)
     */
    void writeCSV(const std::vector<std::tuple<std::string, std::string, double>>& results) const;

    /**
     * Set similarity threshold
     * @param thresh New threshold value
     */
    void setThreshold(double thresh);
};

#endif // REPORTWRITER_H

