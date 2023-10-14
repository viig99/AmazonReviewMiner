#include "spdlog/spdlog.h"
#include "Product.h"

int main() {
    spdlog::info("Hello, World!");
    std::string filename = "../data/meta/meta_AMAZON_FASHION.json.gz";
    AmazonProductDataset dataset(filename);

    auto product = dataset.hasProduct("B00X6KIKXW");
    spdlog::info("Dataset contains B00X6KIKXW = {}", product);
    return 0;
}
