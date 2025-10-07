#include <filesystem>
#include <gtest/gtest.h>
#include "../motion-detector/motion_detector.h"
#include "../benchmark/benchmark.h"
#include "../benchmark_common.h"

// Base configuration tests for LK algorithm
TEST(BenchmarksTest, LKMultiCPU_DefaultConfig) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // config options for LK algorithm:
        detector.getConfig().max_corners = 100;
        detector.getConfig().quality_level = 0.3;
        detector.getConfig().min_distance = 7;
        detector.getConfig().threshold = 2.5;

        detector.getConfig().moving_up_lock_frames = 5;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// High accuracy configuration (more corners, higher quality)
TEST(BenchmarksTest, LKMultiCPU_HighAccuracy) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // High accuracy: more corners, higher quality level
        detector.getConfig().max_corners = 500;
        detector.getConfig().quality_level = 0.5;
        detector.getConfig().min_distance = 5;
        detector.getConfig().threshold = 2.0;
        detector.getConfig().moving_up_lock_frames = 10;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Fast configuration (fewer corners, lower quality)
TEST(BenchmarksTest, LKMultiCPU_FastProcessing) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // Fast: fewer corners, lower quality threshold
        detector.getConfig().max_corners = 50;
        detector.getConfig().quality_level = 0.2;
        detector.getConfig().min_distance = 10;
        detector.getConfig().threshold = 3.0;
        detector.getConfig().moving_up_lock_frames = 3;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Sensitive detection (low threshold, more corners, short lock)
TEST(BenchmarksTest, LKMultiCPU_SensitiveDetection) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // Sensitive: low threshold, more corners, short lock period
        detector.getConfig().max_corners = 200;
        detector.getConfig().quality_level = 0.25;
        detector.getConfig().min_distance = 7;
        detector.getConfig().threshold = 1.5;
        detector.getConfig().moving_up_lock_frames = 2;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Conservative detection (high threshold, fewer corners, long lock)
TEST(BenchmarksTest, LKMultiCPU_ConservativeDetection) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // Conservative: high threshold, fewer corners, long lock period
        detector.getConfig().max_corners = 75;
        detector.getConfig().quality_level = 0.4;
        detector.getConfig().min_distance = 10;
        detector.getConfig().threshold = 4.0;
        detector.getConfig().moving_up_lock_frames = 15;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Large motion configuration (more corners, larger min distance)
TEST(BenchmarksTest, LKMultiCPU_LargeMotion) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // Large motion: more corners spread out, higher quality
        detector.getConfig().max_corners = 300;
        detector.getConfig().quality_level = 0.35;
        detector.getConfig().min_distance = 15;
        detector.getConfig().threshold = 2.5;
        detector.getConfig().moving_up_lock_frames = 5;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// No frame locking (immediate response)
TEST(BenchmarksTest, LKMultiCPU_NoFrameLock) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // No locking for immediate detection response
        detector.getConfig().max_corners = 150;
        detector.getConfig().quality_level = 0.3;
        detector.getConfig().min_distance = 7;
        detector.getConfig().threshold = 2.5;
        detector.getConfig().moving_up_lock_frames = 0;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Extended frame locking (stable detection)
TEST(BenchmarksTest, LKMultiCPU_ExtendedFrameLock) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // Extended locking for very stable detection
        detector.getConfig().max_corners = 150;
        detector.getConfig().quality_level = 0.3;
        detector.getConfig().min_distance = 7;
        detector.getConfig().threshold = 2.5;
        detector.getConfig().moving_up_lock_frames = 20;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}