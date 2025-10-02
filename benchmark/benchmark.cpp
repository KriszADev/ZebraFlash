#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <filesystem>
#include <sstream>

#include "benchmark.h"

#include <unordered_map>

struct Benchmark::Impl {
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
};

Benchmark::Benchmark() : impl(new Impl) {}

void Benchmark::start() {
    impl->start_time = std::chrono::high_resolution_clock::now();
}

double Benchmark::stop() {
    impl->end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = impl->end_time - impl->start_time;
    return elapsed.count();
}

Benchmark::~Benchmark() {
    delete impl;
}

std::vector<CrossIntent> loadGroundTruthCrossingIntent(const std::string& json_filepath) {
    std::vector<CrossIntent> crossing_intent_data;

    std::ifstream file(json_filepath);
    if (!file.is_open()) {
        std::cerr << "Error opening JSON file: " << json_filepath << std::endl;
        return crossing_intent_data;
    }

    nlohmann::json j;
    try {
        file >> j;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return crossing_intent_data;
    }

    for (const auto& pedestrian : j["pedestrians"]) {
        const auto& state_per_frame = pedestrian["state_per_frame"];

        for (auto it = state_per_frame.begin(); it != state_per_frame.end(); ++it) {
            int frame = std::stoi(it.key());
            std::string state = it.value();

            // "zebra felé" means moving towards crossing (is_crossing = true)
            // "áll" means standing/stopped (is_crossing = false)
            bool is_crossing = (state == "zebra felé");

            crossing_intent_data.push_back({frame, is_crossing});
        }
    }

    // Sort by frame number since multiple pedestrians might overlap
    std::sort(crossing_intent_data.begin(), crossing_intent_data.end(),
              [](const CrossIntent& a, const CrossIntent& b) {
                  return a.frame_index < b.frame_index;
              });

    return crossing_intent_data;
}


CrossingMetrics calculateCrossingMetrics(const std::vector<BenchmarkResult>& results, const std::vector<CrossIntent>& ground_truth) {
    CrossingMetrics metrics = {0.0, 0.0, 0.0, 0, 0, 0, 0};

    std::unordered_map<int, bool> ground_truth_map;
    for (const auto& truth : ground_truth) {
        ground_truth_map[truth.frame_index] = truth.is_crossing;
    }

    for (const auto& result : results) {
        bool ground_truth_value = false;
        auto it = ground_truth_map.find(result.frame_index);
        if (it != ground_truth_map.end()) {
            ground_truth_value = it->second;
        }

        if (result.is_crossing && ground_truth_value) {
            metrics.true_positives++;
        } else if (result.is_crossing && !ground_truth_value) {
            metrics.false_positives++;
        } else if (!result.is_crossing && !ground_truth_value) {
            metrics.true_negatives++;
        } else if (!result.is_crossing && ground_truth_value) {
            metrics.false_negatives++;
        }
    }

    int total_crossing = metrics.true_positives + metrics.false_negatives;
    int total_not_crossing = metrics.true_negatives + metrics.false_positives;

    metrics.crossing_accuracy = (total_crossing > 0)
        ? static_cast<double>(metrics.true_positives) / total_crossing
        : 0.0;

    metrics.not_crossing_accuracy = (total_not_crossing > 0)
        ? static_cast<double>(metrics.true_negatives) / total_not_crossing
        : 0.0;

    metrics.balanced_accuracy = (metrics.crossing_accuracy + metrics.not_crossing_accuracy) / 2.0;

    return metrics;
}

void saveResultToCSV(const std::string& filename,
                     const std::vector<BenchmarkResult>& results,
                     const std::vector<CrossIntent>& ground_truth) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    double total_fps = 0.0;
    for (const auto& r : results) {
        if (r.process_time_ms > 0.0) {
            total_fps += 1000.0 / r.process_time_ms;
        }
    }
    double average_fps = results.empty() ? 0.0 : total_fps / results.size();

    CrossingMetrics metrics = calculateCrossingMetrics(results, ground_truth);

    file << "Average FPS:," << std::fixed << std::setprecision(3) << average_fps << "\n";
    file << "\n=== Crossing Intent Metrics ===\n";
    file << "Balanced Accuracy:," << std::setprecision(2) << (metrics.balanced_accuracy * 100) << "%\n";
    file << "Crossing Class Accuracy:," << std::setprecision(2) << (metrics.crossing_accuracy * 100) << "%\n";
    file << "Not Crossing Class Accuracy:," << std::setprecision(2) << (metrics.not_crossing_accuracy * 100) << "%\n";
    file << "\n=== Confusion Matrix ===\n";
    file << "True Positives (Crossing):," << metrics.true_positives << "\n";
    file << "False Positives (Predicted Crossing):," << metrics.false_positives << "\n";
    file << "True Negatives (Not Crossing):," << metrics.true_negatives << "\n";
    file << "False Negatives (Missed Crossing):," << metrics.false_negatives << "\n";

    double precision = (metrics.true_positives + metrics.false_positives > 0)
        ? static_cast<double>(metrics.true_positives) / (metrics.true_positives + metrics.false_positives)
        : 0.0;
    double recall = (metrics.true_positives + metrics.false_negatives > 0)
        ? static_cast<double>(metrics.true_positives) / (metrics.true_positives + metrics.false_negatives)
        : 0.0;
    double f1_score = (precision + recall > 0)
        ? 2 * (precision * recall) / (precision + recall)
        : 0.0;

    file << "\n=== Additional Metrics ===\n";
    file << "Precision:," << std::setprecision(2) << (precision * 100) << "%\n";
    file << "Recall:," << std::setprecision(2) << (recall * 100) << "%\n";
    file << "F1 Score:," << std::setprecision(2) << (f1_score * 100) << "%\n";

    file << "\nFrame Index,Use GPU,FPS,Predicted Intent,Groundtruth Intent,Correct\n";

    std::unordered_map<int, bool> ground_truth_map;
    for (const auto& gt : ground_truth) {
        ground_truth_map[gt.frame_index] = gt.is_crossing;
    }

    for (const auto& r : results) {
        double fps = (r.process_time_ms > 0.0) ? 1000.0 / r.process_time_ms : 0.0;
        bool predicted_intent = r.is_crossing;

        bool groundtruth_intent = false;
        auto gt_it = ground_truth_map.find(r.frame_index);
        if (gt_it != ground_truth_map.end()) {
            groundtruth_intent = gt_it->second;
        }

        bool correct = (predicted_intent == groundtruth_intent);

        file << r.frame_index << ","
             << (r.use_gpu ? "Yes" : "No") << ","
             << std::fixed << std::setprecision(3) << fps << ","
             << (predicted_intent ? "Yes" : "No") << ","
             << (groundtruth_intent ? "Yes" : "No") << ","
             << (correct ? "Yes" : "No") << "\n";
    }
    file.close();
    std::cout << "Results saved to " << filename << std::endl;
}

std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
    return oss.str();
}

void saveBenchmarkResults(const std::vector<BenchmarkResult>& results, const std::string& annotationFile, const std::string& testIdentifier) {
    std::string results_dir = "results";
    if (!std::filesystem::exists(results_dir)) {
        if (!std::filesystem::create_directory(results_dir)) {
            std::cerr << "Error: Could not create 'results' directory." << std::endl;
            return;
        }
    }

    std::string timestamp = getTimestamp();
    std::string detail_filename = results_dir + "/" + testIdentifier + "_benchmark_" + timestamp + ".csv";
    std::string summary_filename = results_dir + "/benchmark_summary.csv";

    std::cout << "Saving benchmark results..." << std::endl;
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    auto ground_truth = loadGroundTruthCrossingIntent(annotationFile);

    saveResultToCSV(detail_filename, results, ground_truth);

    appendToSummaryCSV(summary_filename, testIdentifier, results, ground_truth, detail_filename);
}

void appendToSummaryCSV(const std::string& summary_file,
                        const std::string& testIdentifier,
                        const std::vector<BenchmarkResult>& results,
                        const std::vector<CrossIntent>& ground_truth,
                        const std::string& detail_filename) {

    bool file_exists = std::filesystem::exists(summary_file);
    std::ofstream file(summary_file, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open summary file " << summary_file << std::endl;
        return;
    }

    // Write header if new file
    if (!file_exists) {
        file << "Test ID,Timestamp,Avg FPS,Balanced Accuracy,Crossing Accuracy,Not Crossing Accuracy,"
             << "Precision,Recall,F1 Score,TP,FP,TN,FN,Total Frames,Detail File\n";
    }

    // Calculate metrics
    CrossingMetrics metrics = calculateCrossingMetrics(results, ground_truth);

    double total_fps = 0.0;
    for (const auto& r : results) {
        if (r.process_time_ms > 0.0) {
            total_fps += 1000.0 / r.process_time_ms;
        }
    }
    double avg_fps = results.empty() ? 0.0 : total_fps / results.size();

    double precision = (metrics.true_positives + metrics.false_positives > 0)
        ? static_cast<double>(metrics.true_positives) / (metrics.true_positives + metrics.false_positives)
        : 0.0;
    double recall = (metrics.true_positives + metrics.false_negatives > 0)
        ? static_cast<double>(metrics.true_positives) / (metrics.true_positives + metrics.false_negatives)
        : 0.0;
    double f1_score = (precision + recall > 0)
        ? 2 * (precision * recall) / (precision + recall)
        : 0.0;

    // Extract just the filename from the full path for cleaner summary
    std::string detail_file_short = std::filesystem::path(detail_filename).filename().string();

    file << testIdentifier << ","
         << getTimestamp() << ","
         << std::fixed << std::setprecision(2) << avg_fps << ","
         << std::setprecision(4) << metrics.balanced_accuracy << ","
         << metrics.crossing_accuracy << ","
         << metrics.not_crossing_accuracy << ","
         << precision << ","
         << recall << ","
         << f1_score << ","
         << metrics.true_positives << ","
         << metrics.false_positives << ","
         << metrics.true_negatives << ","
         << metrics.false_negatives << ","
         << results.size() << ","
         << detail_file_short << "\n";

    file.close();
    std::cout << "Summary appended to " << summary_file << std::endl;
}