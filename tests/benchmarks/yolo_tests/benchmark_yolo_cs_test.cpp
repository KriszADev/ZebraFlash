#include <filesystem>
#include <gtest/gtest.h>
#include "../motion-detector/motion_detector.h"
#include "../benchmark/benchmark.h"
#include "../benchmark_common.h"

// Base configuration tests for YOLO algorithm
TEST(BenchmarksTest, YOLOSingleCPU_DefaultConfig) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", false, false,
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
TEST(BenchmarksTest, YOLOSingleCPU_HighAccuracy) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", false, false,
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
TEST(BenchmarksTest, YOLOSingleCPU_FastProcessing) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", false, false,
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
TEST(BenchmarksTest, YOLOSingleCPU_SensitiveDetection) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", false, false,
        [](MotionDetector& d) {
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
TEST(BenchmarksTest, YOLOSingleCPU_ConservativeDetection) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", false, false,
        [](MotionDetector& d) {
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
TEST(BenchmarksTest, YOLOSingleCPU_LargeMotion) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", false, false,
        [](MotionDetector& d) {
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
TEST(BenchmarksTest, YOLOSingleCPU_NoFrameLock) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", false, false,
        [](MotionDetector& d) {
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
TEST(BenchmarksTest, YOLOSingleCPU_ExtendedFrameLock) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", false, false,
        [](MotionDetector& d) {
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
