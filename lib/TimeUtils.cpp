//
// Created by vigi99 on 10/14/23.
//

#include "TimeUtils.h"

Timer::~Timer() {
    auto time_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - start);
    spdlog::info("{} executed in {}ms", name_, time_in_ms.count());
}