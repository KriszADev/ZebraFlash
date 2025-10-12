#include <filesystem>
#include <gtest/gtest.h>
#include "../motion-detector/motion_detector.h"
#include "../benchmark/benchmark.h"
#include "../benchmark_common.h"

// Base configuration tests for YOLO algorithm
TEST(BenchmarksTest, YOLOGPU_DefaultConfig) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            d.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
            d.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
            d.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
            d.getConfig().yolo_confidence_threshold = 0.5;
            d.getConfig().yolo_nms_threshold = 0.4;
            d.getConfig().yolo_input_size = 416;
            d.getConfig().moving_up_lock_frames = 5;
        }
    );
}

// High accuracy configuration (higher confidence, lower NMS threshold)
TEST(BenchmarksTest, YOLOGPU_HighAccuracy) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            d.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
            d.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
            d.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
            d.getConfig().yolo_confidence_threshold = 0.7;
            d.getConfig().yolo_nms_threshold = 0.3;
            d.getConfig().yolo_input_size = 608;
            d.getConfig().moving_up_lock_frames = 10;
        }
    );
}

// Fast configuration (lower confidence, smaller input size)
TEST(BenchmarksTest, YOLOGPU_FastProcessing) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            d.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
            d.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
            d.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
            d.getConfig().yolo_confidence_threshold = 0.3;
            d.getConfig().yolo_nms_threshold = 0.5;
            d.getConfig().yolo_input_size = 320;
            d.getConfig().moving_up_lock_frames = 3;
        }
    );
}

// Sensitive detection (low confidence threshold, short lock)
TEST(BenchmarksTest, YOLOGPU_SensitiveDetection) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            // Sensitive: low confidence threshold, relaxed NMS
            d.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
            d.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
            d.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
            d.getConfig().yolo_confidence_threshold = 0.25;
            d.getConfig().yolo_nms_threshold = 0.5;
            d.getConfig().yolo_input_size = 416;
            d.getConfig().moving_up_lock_frames = 2;
        }
    );
}

// Conservative detection (high confidence threshold, long lock)
TEST(BenchmarksTest, YOLOGPU_ConservativeDetection) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            // Conservative: high confidence threshold, strict NMS, long lock
            d.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
            d.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
            d.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
            d.getConfig().yolo_confidence_threshold = 0.75;
            d.getConfig().yolo_nms_threshold = 0.3;
            d.getConfig().yolo_input_size = 416;
            d.getConfig().moving_up_lock_frames = 15;
        }
    );
}

// Large motion configuration (larger input size for better detection)
TEST(BenchmarksTest, YOLOGPU_LargeMotion) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            // Large motion: larger input size, balanced thresholds
            d.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
            d.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
            d.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
            d.getConfig().yolo_confidence_threshold = 0.5;
            d.getConfig().yolo_nms_threshold = 0.4;
            d.getConfig().yolo_input_size = 608;
            d.getConfig().moving_up_lock_frames = 5;
        }
    );
}

// No frame locking (immediate response)
TEST(BenchmarksTest, YOLOGPU_NoFrameLock) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            // No locking for immediate detection response
            d.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
            d.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
            d.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
            d.getConfig().yolo_confidence_threshold = 0.5;
            d.getConfig().yolo_nms_threshold = 0.4;
            d.getConfig().yolo_input_size = 416;
            d.getConfig().moving_up_lock_frames = 0;
        }
    );
}

// Extended frame locking (stable detection)
TEST(BenchmarksTest, YOLOGPU_ExtendedFrameLock) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            // Extended locking for very stable detection
            d.getConfig().yolo_weights_path = "../../input/yolo/yolov4-tiny.weights";
            d.getConfig().yolo_config_path = "../../input/yolo/yolov4-tiny.cfg";
            d.getConfig().yolo_classes_path = "../../input/yolo/coco.names";
            d.getConfig().yolo_confidence_threshold = 0.5;
            d.getConfig().yolo_nms_threshold = 0.4;
            d.getConfig().yolo_input_size = 416;
            d.getConfig().moving_up_lock_frames = 20;
        }
    );
}