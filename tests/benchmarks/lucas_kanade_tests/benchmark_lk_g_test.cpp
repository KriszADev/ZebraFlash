#include <filesystem>
#include <gtest/gtest.h>
#include "../motion-detector/motion_detector.h"
#include "../benchmark/benchmark.h"
#include "../benchmark_common.h"

// Base configuration tests for LK algorithm
TEST(BenchmarksTest, LKGPU_DefaultConfig) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", true, false,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 100;
            d.getConfig().quality_level = 0.3;
            d.getConfig().min_distance = 7;
            d.getConfig().threshold = 2.5;
            d.getConfig().moving_up_lock_frames = 5;
        }
    );
}

// High accuracy configuration (more corners, higher quality)
TEST(BenchmarksTest, LKGPU_HighAccuracy) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", true, false,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 500;
            d.getConfig().quality_level = 0.5;
            d.getConfig().min_distance = 5;
            d.getConfig().threshold = 2.0;
            d.getConfig().moving_up_lock_frames = 10;
        }
    );
}

// Fast configuration (fewer corners, lower quality)
TEST(BenchmarksTest, LKGPU_FastProcessing) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", true, false,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 50;
            d.getConfig().quality_level = 0.2;
            d.getConfig().min_distance = 10;
            d.getConfig().threshold = 3.0;
            d.getConfig().moving_up_lock_frames = 3;
        }
    );
}

// Sensitive detection (low threshold, more corners, short lock)
TEST(BenchmarksTest, LKGPU_SensitiveDetection) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", true, false,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 200;
            d.getConfig().quality_level = 0.25;
            d.getConfig().min_distance = 7;
            d.getConfig().threshold = 1.5;
            d.getConfig().moving_up_lock_frames = 2;
        }
    );
}

// Conservative detection (high threshold, fewer corners, long lock)
TEST(BenchmarksTest, LKGPU_ConservativeDetection) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", true, false,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 75;
            d.getConfig().quality_level = 0.4;
            d.getConfig().min_distance = 10;
            d.getConfig().threshold = 4.0;
            d.getConfig().moving_up_lock_frames = 15;
        }
    );
}

// Large motion configuration (more corners, larger min distance)
TEST(BenchmarksTest, LKGPU_LargeMotion) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", true, false,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 300;
            d.getConfig().quality_level = 0.35;
            d.getConfig().min_distance = 15;
            d.getConfig().threshold = 2.5;
            d.getConfig().moving_up_lock_frames = 5;
        }
    );
}

// No frame locking (immediate response)
TEST(BenchmarksTest, LKGPU_NoFrameLock) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", true, false,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 150;
            d.getConfig().quality_level = 0.3;
            d.getConfig().min_distance = 7;
            d.getConfig().threshold = 2.5;
            d.getConfig().moving_up_lock_frames = 0;
        }
    );
}

// Extended frame locking (stable detection)
TEST(BenchmarksTest, LKGPU_ExtendedFrameLock) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "LK", true, false,
        [](MotionDetector& d) {
            d.getConfig().max_corners = 150;
            d.getConfig().quality_level = 0.3;
            d.getConfig().min_distance = 7;
            d.getConfig().threshold = 2.5;
            d.getConfig().moving_up_lock_frames = 20;
        }
    );
}