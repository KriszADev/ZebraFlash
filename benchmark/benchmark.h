#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <string>
#include <vector>

class Benchmark {
public:
    Benchmark();
    ~Benchmark();

    void start();
    double stop();

private:
    struct Impl;
    Impl *impl;
};

struct BenchmarkResult {
    int frame_index;
    bool use_gpu;
    double process_time_ms;
    bool is_crossing;
};

struct CrossIntent {
    int frame_index;
    bool is_crossing;
};

struct CrossingMetrics {
    double balanced_accuracy;
    double crossing_accuracy;
    double not_crossing_accuracy;
    int true_positives;   // Correctly predicted crossing
    int false_positives;  // Predicted crossing, was not crossing
    int true_negatives;   // Correctly predicted not crossing
    int false_negatives;  // Predicted not crossing, was crossing
};

std::string getTimestamp();
std::vector<CrossIntent> loadGroundTruthCrossingIntent(const std::string& xml_filepath);
CrossingMetrics calculateCrossingMetrics(const std::vector<BenchmarkResult>& results, const std::vector<CrossIntent>& ground_truth);
void saveResultToCSV(const std::string& filename, const std::vector<BenchmarkResult>& results);
void saveBenchmarkResults(const std::vector<BenchmarkResult>& results, const std::string& annotationFile, const std::string& testIdentifier);
void appendToSummaryCSV(const std::string& summary_file, const std::string& test_config, const std::vector<BenchmarkResult>& results, const std::vector<CrossIntent>& ground_truth, const std::string& detail_filename);

#endif //BENCHMARK_H
