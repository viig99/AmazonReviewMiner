//
// Created by vigi99 on 10/14/23.
//

#pragma once

#include <string>
#include <zlib.h>
#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"
#include <coro/coro.hpp>

using namespace nlohmann;

class JSONLReader {
    public:
        static coro::generator<json> generate(std::string& filename );
};
