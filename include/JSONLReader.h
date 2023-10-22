//
// Created by vigi99 on 10/14/23.
//

#pragma once

#if defined(__SSE4_2__)
#  define RAPIDJSON_SSE42
#elif defined(__SSE2__)
#  define RAPIDJSON_SSE2
#elif defined(__ARM_NEON)
#  define RAPIDJSON_NEON
#endif

#include <string>
#include <zlib.h>
#include <spdlog/spdlog.h>
#include <rapidjson/document.h>
#include <coro/coro.hpp>

using namespace rapidjson;
using namespace std;

class JSONLReader {
public:
    static coro::generator<Document> generate(const string &filename);
};
