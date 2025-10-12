#pragma once
#include <string>
#include <filesystem>
#include <motion_detector.h>

#ifndef BENCHMARK_COMMON_H
#define BENCHMARK_COMMON_H

namespace BenchmarkHelpers {
    inline std::string getInputFile() {
        return "../../config/params_input_file.yml";
    }

    inline std::string getVideoSrc(int video) {
        switch (video) {
            case 1: return "../../input/IMG_7885.MP4";
            case 2: return "../../input/IMG_7874.MP4";
            default: return "";
        }
    }

    inline std::string getVideoAnnot(int video) {
        switch (video) {
            case 1: return "../../input/IMG_7885.json";
            case 2: return "../../input/IMG_7874.json";
            default: return "";
        }
    }

    inline void setCommonConfig(MotionDetector& detector, int video) {
        detector.getConfig().debug = false;
        detector.getConfig().video_src = getVideoSrc(video);
        detector.getConfig().video_annot = getVideoAnnot(video);
        detector.getConfig().seek = 0;
        detector.getConfig().seek_end = 0;
    }

    inline void runBenchmarkTest(
        const std::string& testId,
        const std::string& algorithm,
        bool useGpu,
        bool useMultiThread,
        const std::function<void(MotionDetector&)>& configFunc,
        const std::vector<int>& videos = {1, 2}
    ) {
        for (int video : videos) {
            std::string fullTestId = testId + "_video" + std::to_string(video);

            try {
                MotionDetector detector(getInputFile(), fullTestId);
                detector.getConfig().algorithm = algorithm;
                detector.getConfig().use_gpu = useGpu;
                detector.getConfig().use_multi_thread = useMultiThread;
                setCommonConfig(detector, video);

                configFunc(detector);

                detector.run();
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                throw;
            }

            if (!std::filesystem::exists("results/" + fullTestId  + "_benchmark_" + getTimestamp() + ".csv")) {
                std::cout << "results/" + fullTestId + "_benchmark_" + getTimestamp() + ".csv" << std::endl;
                throw std::runtime_error("Benchmark file was not created for video " + std::to_string(video));
            }
        }
    }
}

#endif //BENCHMARK_COMMON_H
