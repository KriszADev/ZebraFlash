#include <filesystem>
#include <gtest/gtest.h>
#include "../motion-detector/motion_detector.h"
#include "../benchmark/benchmark.h"
#include "../benchmark_common.h"

// Base configuration tests for YOLO algorithm
TEST(BenchmarksTest, YOLOSingleCPU_DefaultConfig) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // config options for YOLO algorithm:
        detector.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
        detector.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
        detector.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
        detector.getConfig().yolo_confidence_threshold = 0.5;
        detector.getConfig().yolo_nms_threshold = 0.4;
        detector.getConfig().yolo_input_size = 416;

        detector.getConfig().moving_up_lock_frames = 5;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// High accuracy configuration (higher confidence, lower NMS threshold)
TEST(BenchmarksTest, YOLOSingleCPU_HighAccuracy) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // High accuracy: higher confidence threshold, stricter NMS, larger input
        detector.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
        detector.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
        detector.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
        detector.getConfig().yolo_confidence_threshold = 0.7;
        detector.getConfig().yolo_nms_threshold = 0.3;
        detector.getConfig().yolo_input_size = 608;
        detector.getConfig().moving_up_lock_frames = 10;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Fast configuration (lower confidence, smaller input size)
TEST(BenchmarksTest, YOLOSingleCPU_FastProcessing) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // Fast: lower confidence, smaller input size for speed
        detector.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
        detector.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
        detector.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
        detector.getConfig().yolo_confidence_threshold = 0.3;
        detector.getConfig().yolo_nms_threshold = 0.5;
        detector.getConfig().yolo_input_size = 320;
        detector.getConfig().moving_up_lock_frames = 3;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Sensitive detection (low confidence threshold, short lock)
TEST(BenchmarksTest, YOLOSingleCPU_SensitiveDetection) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // Sensitive: low confidence threshold, relaxed NMS
        detector.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
        detector.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
        detector.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
        detector.getConfig().yolo_confidence_threshold = 0.25;
        detector.getConfig().yolo_nms_threshold = 0.5;
        detector.getConfig().yolo_input_size = 416;
        detector.getConfig().moving_up_lock_frames = 2;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Conservative detection (high confidence threshold, long lock)
TEST(BenchmarksTest, YOLOSingleCPU_ConservativeDetection) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // Conservative: high confidence threshold, strict NMS, long lock
        detector.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
        detector.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
        detector.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
        detector.getConfig().yolo_confidence_threshold = 0.75;
        detector.getConfig().yolo_nms_threshold = 0.3;
        detector.getConfig().yolo_input_size = 416;
        detector.getConfig().moving_up_lock_frames = 15;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Large motion configuration (larger input size for better detection)
TEST(BenchmarksTest, YOLOSingleCPU_LargeMotion) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // Large motion: larger input size, balanced thresholds
        detector.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
        detector.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
        detector.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
        detector.getConfig().yolo_confidence_threshold = 0.5;
        detector.getConfig().yolo_nms_threshold = 0.4;
        detector.getConfig().yolo_input_size = 608;
        detector.getConfig().moving_up_lock_frames = 5;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// No frame locking (immediate response)
TEST(BenchmarksTest, YOLOSingleCPU_NoFrameLock) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // No locking for immediate detection response
        detector.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
        detector.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
        detector.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
        detector.getConfig().yolo_confidence_threshold = 0.5;
        detector.getConfig().yolo_nms_threshold = 0.4;
        detector.getConfig().yolo_input_size = 416;
        detector.getConfig().moving_up_lock_frames = 0;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Extended frame locking (stable detection)
TEST(BenchmarksTest, YOLOSingleCPU_ExtendedFrameLock) {
    const std::string testId = test_info_->name();

    try {
        MotionDetector detector(BenchmarkHelpers::getInputFile(),
            testId);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        BenchmarkHelpers::setCommonConfig(detector, 1);

        // Extended locking for very stable detection
        detector.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
        detector.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
        detector.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
        detector.getConfig().yolo_confidence_threshold = 0.5;
        detector.getConfig().yolo_nms_threshold = 0.4;
        detector.getConfig().yolo_input_size = 416;
        detector.getConfig().moving_up_lock_frames = 20;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/" + testId + "_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}