#include "spdlog/spdlog.h"
#include "Product.h"

int main() {
    spdlog::info("Hello, World!");
    std::string filename = "../data/meta/meta_AMAZON_FASHION.json.gz";
    AmazonProductDataset dataset(filename);
    return 0;
}
