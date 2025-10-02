#include <filesystem>
#include <gtest/gtest.h>
#include "../motion-detector/motion_detector.h"
#include "../benchmark/benchmark.h"

// Base configuration tests for each algorithm
TEST(BenchmarksTest, FarneSingleCPU_DefaultConfig) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE, test_info_->name());
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/IMG_7885.MP4";
        detector.getConfig().video_annot = "../../input/gyalogosok_IMG_7885.json";
        detector.getConfig().seek_end = 2500;

        // config options for FARNE algorithm:
        detector.getConfig().pyr_scale = 0.5;
        detector.getConfig().levels = 1;
        detector.getConfig().winsize = 25;
        detector.getConfig().iterations = 1;
        detector.getConfig().poly_n = 5;
        detector.getConfig().poly_sigma = 1.1;
        detector.getConfig().threshold = 2.5;

        detector.getConfig().moving_up_lock_frames = 5;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_FARNE_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

// High accuracy configuration (more pyramid levels, larger window)
TEST(BenchmarksTest, FarneSingleCPU_HighAccuracy) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE, test_info_->name());
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/IMG_7885.MP4";
        detector.getConfig().video_annot = "../../input/gyalogosok_IMG_7885.json";
        detector.getConfig().seek_end = 2500;

        // High accuracy: more levels, larger window, more iterations
        detector.getConfig().pyr_scale = 0.5;
        detector.getConfig().levels = 5;
        detector.getConfig().winsize = 25;
        detector.getConfig().iterations = 5;
        detector.getConfig().poly_n = 7;
        detector.getConfig().poly_sigma = 1.5;
        detector.getConfig().threshold = 2.0;
        detector.getConfig().moving_up_lock_frames = 10;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_FARNE_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Fast configuration (minimal levels and iterations)
TEST(BenchmarksTest, FarneSingleCPU_FastProcessing) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE, test_info_->name());
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/IMG_7885.MP4";
        detector.getConfig().video_annot = "../../input/gyalogosok_IMG_7885.json";
        detector.getConfig().seek_end = 2500;

        // Fast: minimal levels and iterations
        detector.getConfig().pyr_scale = 0.5;
        detector.getConfig().levels = 1;
        detector.getConfig().winsize = 10;
        detector.getConfig().iterations = 1;
        detector.getConfig().poly_n = 5;
        detector.getConfig().poly_sigma = 1.1;
        detector.getConfig().threshold = 3.0;
        detector.getConfig().moving_up_lock_frames = 3;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_FARNE_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Sensitive detection (low threshold, short lock)
TEST(BenchmarksTest, FarneSingleCPU_SensitiveDetection) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE, test_info_->name());
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/IMG_7885.MP4";
        detector.getConfig().video_annot = "../../input/gyalogosok_IMG_7885.json";
        detector.getConfig().seek_end = 2500;

        // Sensitive: low threshold, short lock period
        detector.getConfig().pyr_scale = 0.5;
        detector.getConfig().levels = 3;
        detector.getConfig().winsize = 15;
        detector.getConfig().iterations = 3;
        detector.getConfig().poly_n = 5;
        detector.getConfig().poly_sigma = 1.1;
        detector.getConfig().threshold = 1.5;
        detector.getConfig().moving_up_lock_frames = 2;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_FARNE_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Conservative detection (high threshold, long lock)
TEST(BenchmarksTest, FarneSingleCPU_ConservativeDetection) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE, test_info_->name());
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/IMG_7885.MP4";
        detector.getConfig().video_annot = "../../input/gyalogosok_IMG_7885.json";
        detector.getConfig().seek_end = 2500;

        // Conservative: high threshold, long lock period
        detector.getConfig().pyr_scale = 0.5;
        detector.getConfig().levels = 3;
        detector.getConfig().winsize = 15;
        detector.getConfig().iterations = 3;
        detector.getConfig().poly_n = 5;
        detector.getConfig().poly_sigma = 1.1;
        detector.getConfig().threshold = 4.0;
        detector.getConfig().moving_up_lock_frames = 15;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_FARNE_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Large motion configuration (larger pyramid scale and window)
TEST(BenchmarksTest, FarneSingleCPU_LargeMotion) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE, test_info_->name());
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/IMG_7885.MP4";
        detector.getConfig().video_annot = "../../input/gyalogosok_IMG_7885.json";
        detector.getConfig().seek_end = 2500;

        // Large motion: larger pyramid scale, larger window
        detector.getConfig().pyr_scale = 0.8;
        detector.getConfig().levels = 4;
        detector.getConfig().winsize = 30;
        detector.getConfig().iterations = 3;
        detector.getConfig().poly_n = 7;
        detector.getConfig().poly_sigma = 1.5;
        detector.getConfig().threshold = 2.5;
        detector.getConfig().moving_up_lock_frames = 5;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_FARNE_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// No frame locking (immediate response)
TEST(BenchmarksTest, FarneSingleCPU_NoFrameLock) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE, test_info_->name());
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/IMG_7885.MP4";
        detector.getConfig().video_annot = "../../input/gyalogosok_IMG_7885.json";
        detector.getConfig().seek_end = 2500;

        // No locking for immediate detection response
        detector.getConfig().pyr_scale = 0.5;
        detector.getConfig().levels = 3;
        detector.getConfig().winsize = 15;
        detector.getConfig().iterations = 3;
        detector.getConfig().poly_n = 5;
        detector.getConfig().poly_sigma = 1.1;
        detector.getConfig().threshold = 2.5;
        detector.getConfig().moving_up_lock_frames = 0;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_FARNE_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

// Extended frame locking (stable detection)
TEST(BenchmarksTest, FarneSingleCPU_ExtendedFrameLock) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE, test_info_->name());
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/IMG_7885.MP4";
        detector.getConfig().video_annot = "../../input/gyalogosok_IMG_7885.json";
        detector.getConfig().seek_end = 2500;

        // Extended locking for very stable detection
        detector.getConfig().pyr_scale = 0.5;
        detector.getConfig().levels = 3;
        detector.getConfig().winsize = 15;
        detector.getConfig().iterations = 3;
        detector.getConfig().poly_n = 5;
        detector.getConfig().poly_sigma = 1.1;
        detector.getConfig().threshold = 2.5;
        detector.getConfig().moving_up_lock_frames = 20;

        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_FARNE_benchmark_" + getTimestamp() + ".csv"))
        << "Benchmark file was not created.";
}

/*TEST(BenchmarksTest, TestFarneSingleCPUDayShadow) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad2.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad2_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_FARNE_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestFarneSingleCPUNight) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad3.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad3_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_FARNE_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestFarneMultiCPUCrowd) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad1.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad1_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_FARNE_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestFarneMultiCPUDayShadow) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad2.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad2_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_FARNE_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestFarneMultiCPUNight) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad3.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad3_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_FARNE_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestFarneGPUCrowd) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = true;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad1.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad1_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/gpu_FARNE_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestFarneGPUDayShadow) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = true;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad2.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad2_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/gpu_FARNE_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestFarneGPUNight) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "FARNE";
        detector.getConfig().use_gpu = true;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad3.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad3_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/gpu_FARNE_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestLKMultiCPUCrowd) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad1.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad1_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_LK_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestLKMultiCPUDayShadow) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad2.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad2_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_LK_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestLKMultiCPUNight) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = true;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad3.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad3_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_LK_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestLKGPUCrowd) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = true;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad1.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad1_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/gpu_LK_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestLKGPUDayShadow) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = true;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad2.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad2_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/gpu_LK_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestLKGPUNight) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "LK";
        detector.getConfig().use_gpu = true;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad3.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad3_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/gpu_LK_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestYOLOSingleCPUCrowd) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad1.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad1_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_YOLO_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestYOLOSingleCPUDayShadow) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad2.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad2_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_YOLO_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestYOLOSingleCPUNight) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = false;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad3.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad3_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/cpu_YOLO_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestYOLOGPUCrowd) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = true;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad1.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad1_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/gpu_YOLO_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestYOLOGPUDayShadow) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = true;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad2.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad2_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/gpu_YOLO_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}

TEST(BenchmarksTest, TestYOLOGPUNight) {
    const std::string INPUT_FILE = "../../config/params_input_file.yml";

    try {
        MotionDetector detector(INPUT_FILE);
        detector.getConfig().algorithm = "YOLO";
        detector.getConfig().use_gpu = true;
        detector.getConfig().use_multi_thread = false;
        detector.getConfig().debug = false;
        detector.getConfig().video_src = "../../input/abbeyroad3.mp4";
        detector.getConfig().video_annot = "../../input/abbeyroad3_annotation.csv";
        detector.getConfig().seek_end = 2500;
        detector.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ASSERT_TRUE(std::filesystem::exists("results/gpu_YOLO_benchmark_" + getTimestamp()) + ".csv") << "Benchmark file was not created.";
}*/