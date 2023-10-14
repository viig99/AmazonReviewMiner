//
// Created by vigi99 on 10/14/23.
//

#pragma once

#include <chrono>
#include <utility>
#include "spdlog/spdlog.h"

class Timer {
public:
    explicit Timer(std::string  name): start(std::chrono::high_resolution_clock::now()), name_{std::move(name)} {};
    ~Timer();

private:
    std::chrono::system_clock::time_point start;
    std::string name_;
};