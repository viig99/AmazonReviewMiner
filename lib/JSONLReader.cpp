#include "JSONLReader.h"

coro::generator<Document> JSONLReader::generate(const string &filename) {
    gzFile file = gzopen(filename.c_str(), "rb");
    if (!file) {
        spdlog::error("Could not open file {}", filename);
        co_return;
    }
    char buffer[1024*64];
    string line;
    while (true) {
        if (gzgets(file, buffer, sizeof(buffer)) == Z_NULL) break;
        line += buffer;
        if (line.back() == '\n') {
            line.pop_back();
            Document document;
            co_yield std::move(document.Parse(line.c_str()));
            line.clear();
        }
    }

    gzclose(file);
}