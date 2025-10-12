#include <filesystem>
#include <gtest/gtest.h>
#include "../motion-detector/motion_detector.h"
#include "../benchmark/benchmark.h"
#include "../benchmark_common.h"

// Base configuration tests for each algorithm
TEST(BenchmarksTest, FarneGPU_DefaultConfig) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "FARNE", true, false,
        [](MotionDetector& d) {
            d.getConfig().pyr_scale = 0.5;
            d.getConfig().levels = 1;
            d.getConfig().winsize = 25;
            d.getConfig().iterations = 1;
            d.getConfig().poly_n = 5;
            d.getConfig().poly_sigma = 1.1;
            d.getConfig().threshold = 2.5;
            d.getConfig().moving_up_lock_frames = 5;
        }
    );
}

// High accuracy configuration (more pyramid levels, larger window)
TEST(BenchmarksTest, FarneGPU_HighAccuracy) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "FARNE", true, false,
        [](MotionDetector& d) {
            d.getConfig().pyr_scale = 0.5;
            d.getConfig().levels = 5;
            d.getConfig().winsize = 25;
            d.getConfig().iterations = 5;
            d.getConfig().poly_n = 7;
            d.getConfig().poly_sigma = 1.5;
            d.getConfig().threshold = 2.0;
            d.getConfig().moving_up_lock_frames = 10;
        }
    );
}

// Fast configuration (minimal levels and iterations)
TEST(BenchmarksTest, FarneGPU_FastProcessing) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "FARNE", true, false,
        [](MotionDetector& d) {
            d.getConfig().pyr_scale = 0.5;
            d.getConfig().levels = 1;
            d.getConfig().winsize = 10;
            d.getConfig().iterations = 1;
            d.getConfig().poly_n = 5;
            d.getConfig().poly_sigma = 1.1;
            d.getConfig().threshold = 3.0;
            d.getConfig().moving_up_lock_frames = 3;
        }
    );
}

// Sensitive detection (low threshold, short lock)
TEST(BenchmarksTest, FarneGPU_SensitiveDetection) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "FARNE", true, false,
        [](MotionDetector& d) {
            d.getConfig().pyr_scale = 0.5;
            d.getConfig().levels = 3;
            d.getConfig().winsize = 15;
            d.getConfig().iterations = 3;
            d.getConfig().poly_n = 5;
            d.getConfig().poly_sigma = 1.1;
            d.getConfig().threshold = 1.5;
            d.getConfig().moving_up_lock_frames = 2;
        }
    );
}

// Conservative detection (high threshold, long lock)
TEST(BenchmarksTest, FarneGPU_ConservativeDetection) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "FARNE", true, false,
        [](MotionDetector& d) {
            d.getConfig().pyr_scale = 0.5;
            d.getConfig().levels = 3;
            d.getConfig().winsize = 15;
            d.getConfig().iterations = 3;
            d.getConfig().poly_n = 5;
            d.getConfig().poly_sigma = 1.1;
            d.getConfig().threshold = 4.0;
            d.getConfig().moving_up_lock_frames = 15;
        }
    );
}

// Large motion configuration (larger pyramid scale and window)
TEST(BenchmarksTest, FarneGPU_LargeMotion) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "FARNE", true, false,
        [](MotionDetector& d) {
            d.getConfig().pyr_scale = 0.8;
            d.getConfig().levels = 4;
            d.getConfig().winsize = 30;
            d.getConfig().iterations = 3;
            d.getConfig().poly_n = 7;
            d.getConfig().poly_sigma = 1.5;
            d.getConfig().threshold = 2.5;
            d.getConfig().moving_up_lock_frames = 5;
        }
    );
}

// No frame locking (immediate response)
TEST(BenchmarksTest, FarneGPU_NoFrameLock) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "FARNE", true, false,
        [](MotionDetector& d) {
            d.getConfig().pyr_scale = 0.5;
            d.getConfig().levels = 3;
            d.getConfig().winsize = 15;
            d.getConfig().iterations = 3;
            d.getConfig().poly_n = 5;
            d.getConfig().poly_sigma = 1.1;
            d.getConfig().threshold = 2.5;
            d.getConfig().moving_up_lock_frames = 0;
        }
    );
}

// Extended frame locking (stable detection)
TEST(BenchmarksTest, FarneGPU_ExtendedFrameLock) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "FARNE", true, false,
        [](MotionDetector& d) {
            d.getConfig().pyr_scale = 0.5;
            d.getConfig().levels = 3;
            d.getConfig().winsize = 15;
            d.getConfig().iterations = 3;
            d.getConfig().poly_n = 5;
            d.getConfig().poly_sigma = 1.1;
            d.getConfig().threshold = 2.5;
            d.getConfig().moving_up_lock_frames = 20;
        }
    );
}