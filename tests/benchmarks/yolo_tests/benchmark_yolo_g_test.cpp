#include <filesystem>
#include <gtest/gtest.h>
#include "../motion-detector/motion_detector.h"
#include "../benchmark/benchmark.h"
#include "../benchmark_common.h"

// Base configuration tests for YOLO algorithm
TEST(BenchmarksTest, YOLOGPU_DefaultConfig) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            BenchmarkHelpers::setYOLOFiles(d);
            d.getConfig().yolo_confidence_threshold = 0.5;
            d.getConfig().yolo_nms_threshold = 0.4;
            d.getConfig().yolo_input_size = 416;
        }
    );
}

// High accuracy configuration (higher confidence, lower NMS threshold)
TEST(BenchmarksTest, YOLOGPU_HighAccuracy) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            BenchmarkHelpers::setYOLOFiles(d);
            d.getConfig().yolo_confidence_threshold = 0.7;
            d.getConfig().yolo_nms_threshold = 0.3;
            d.getConfig().yolo_input_size = 608;
        }
    );
}

// Fast configuration (lower confidence, smaller input size)
TEST(BenchmarksTest, YOLOGPU_FastProcessing) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            BenchmarkHelpers::setYOLOFiles(d);
            d.getConfig().yolo_confidence_threshold = 0.3;
            d.getConfig().yolo_nms_threshold = 0.5;
            d.getConfig().yolo_input_size = 320;
        }
    );
}

// Sensitive detection (low confidence threshold, short lock)
TEST(BenchmarksTest, YOLOGPU_SensitiveDetection) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            BenchmarkHelpers::setYOLOFiles(d);
            d.getConfig().yolo_confidence_threshold = 0.25;
            d.getConfig().yolo_nms_threshold = 0.5;
            d.getConfig().yolo_input_size = 416;
        }
    );
}

// Conservative detection (high confidence threshold, long lock)
TEST(BenchmarksTest, YOLOGPU_ConservativeDetection) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            BenchmarkHelpers::setYOLOFiles(d);
            d.getConfig().yolo_confidence_threshold = 0.75;
            d.getConfig().yolo_nms_threshold = 0.3;
            d.getConfig().yolo_input_size = 416;
        }
    );
}

// Large motion configuration (larger input size for better detection)
TEST(BenchmarksTest, YOLOGPU_LargeMotion) {
    BenchmarkHelpers::runBenchmarkTest(test_info_->name(), "YOLO", true, false,
        [](MotionDetector& d) {
            BenchmarkHelpers::setYOLOFiles(d);
            d.getConfig().yolo_confidence_threshold = 0.5;
            d.getConfig().yolo_nms_threshold = 0.4;
            d.getConfig().yolo_input_size = 608;
        }
    );
}