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
            case 2: return "../../input/test_clip.MP4";
            case 3: return "../../input/test_clip2.MP4";
            default: return "";
        }
    }

    inline std::string getVideoAnnot(int video) {
        switch (video) {
            case 1: return "../../input/gyalogosok_IMG_7885.json";
            case 2: return "../../input/test_clip.MP4";
            case 3: return "../../input/test_clip2.MP4";
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
}

#endif //BENCHMARK_COMMON_H
