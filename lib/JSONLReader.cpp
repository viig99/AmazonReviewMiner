#include "JSONLReader.h"

coro::generator<json> JSONLReader::generate(std::string& filename) {
    gzFile file = gzopen(filename.c_str(), "rb");
    if (!file) {
        spdlog::error("Could not open file {}", filename);
        co_return;
    }
    char buffer[1024];
    std::string line;
    while (true) {
        if (gzgets(file, buffer, sizeof(buffer)) == Z_NULL) break;
        line += buffer;
        if (line.back() == '\n') {
            line.pop_back();
            auto j = json::parse(line);
            co_yield j;
            line.clear();
        }
    }

    gzclose(file);
}