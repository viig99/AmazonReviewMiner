#include "spdlog/spdlog.h"
#include "JSONLReader.h"

int main() {
    spdlog::info("Hello, World!");
    std::string filename = "../data/meta/meta_AMAZON_FASHION.json.gz";
    JSONLReader::generate(filename);
    return 0;
}
