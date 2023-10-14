#include "JSONLReader.h"

int JSONLReader::generate(std::string& filename) {
    gzFile file = gzopen(filename.c_str(), "rb");
    if (!file) {
        spdlog::error("Could not open file {}", filename);
        return 1;
    }
    char buffer[1024];
    std::string line;
    while (true) {
        if (gzgets(file, buffer, sizeof(buffer)) == Z_NULL) break;
        line += buffer;
        if (line.back() == '\n') {
            line.pop_back();
            auto j = nlohmann::json::parse(line);
            spdlog::info(j["asin"]);
            line.clear();
        }
    }

    gzclose(file);
    return 0;
}