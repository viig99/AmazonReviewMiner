//
// Created by vigi99 on 10/14/23.
//

#pragma once

#include <string>
#include <zlib.h>
#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"

class JSONLReader {
    public:
        static int generate(std::string& filename );
};
