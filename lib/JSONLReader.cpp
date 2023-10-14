#include "JSONLReader.h"

coro::generator<Document> JSONLReader::generate(const string &filename) {
    gzFile file = gzopen(filename.c_str(), "rb");
    if (!file) {
        spdlog::error("Could not open file {}", filename);
        co_return;
    }
    char buffer[4096];
    string line;
    Document document;
    while (true) {
        if (gzgets(file, buffer, sizeof(buffer)) == Z_NULL) break;
        line += buffer;
        if (line.back() == '\n') {
            line.pop_back();
            co_yield document.Parse(line.c_str());
            line.clear();
        }
    }

    gzclose(file);
}