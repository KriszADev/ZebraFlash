#include <filesystem>
#include <gtest/gtest.h>
#include "../motion-detector/motion_detector.h"
#include "../benchmark/benchmark.h"
#include "../benchmark_common.h"

// Base configuration tests for LK algorithm
TEST(BenchmarksTest, LKMultiCPU_DefaultConfig) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", false, true,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 100;
            d.getConfig().quality_level = 0.3;
            d.getConfig().min_distance = 7;
            d.getConfig().threshold = 2.5;
        }
    );
}

// High accuracy configuration (more corners, higher quality)
TEST(BenchmarksTest, LKMultiCPU_HighAccuracy) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", false, true,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 500;
            d.getConfig().quality_level = 0.5;
            d.getConfig().min_distance = 5;
            d.getConfig().threshold = 2.0;
        }
    );
}

// Fast configuration (fewer corners, lower quality)
TEST(BenchmarksTest, LKMultiCPU_FastProcessing) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", false, true,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 50;
            d.getConfig().quality_level = 0.2;
            d.getConfig().min_distance = 10;
            d.getConfig().threshold = 3.0;
        }
    );
}

// Sensitive detection (low threshold, more corners, short lock)
TEST(BenchmarksTest, LKMultiCPU_SensitiveDetection) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", false, true,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 200;
            d.getConfig().quality_level = 0.25;
            d.getConfig().min_distance = 7;
            d.getConfig().threshold = 1.5;
        }
    );
}

// Conservative detection (high threshold, fewer corners, long lock)
TEST(BenchmarksTest, LKMultiCPU_ConservativeDetection) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", false, true,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 75;
            d.getConfig().quality_level = 0.4;
            d.getConfig().min_distance = 10;
            d.getConfig().threshold = 4.0;
        }
    );
}

// Large motion configuration (more corners, larger min distance)
TEST(BenchmarksTest, LKMultiCPU_LargeMotion) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", false, true,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 300;
            d.getConfig().quality_level = 0.35;
            d.getConfig().min_distance = 15;
            d.getConfig().threshold = 2.5;
        }
    );
}