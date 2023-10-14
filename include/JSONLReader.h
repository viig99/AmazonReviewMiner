//
// Created by vigi99 on 10/14/23.
//

#pragma once

#include <string>
#include <zlib.h>
#include <spdlog/spdlog.h>
#include <rapidjson/document.h>
#include <coro/coro.hpp>

using namespace rapidjson;
using namespace std;

class JSONLReader {
    public:
        static coro::generator<Document> generate(const string& filename );
};
