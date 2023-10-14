#include "spdlog/spdlog.h"
#include "JSONLReader.h"

int main() {
    spdlog::info("Hello, World!");
    std::string filename = "../data/meta/meta_AMAZON_FASHION.json.gz";
    for (auto j : JSONLReader::generate(filename)) {
        spdlog::info("{}", j.dump());
    }
    return 0;
}
