#include "spdlog/spdlog.h"
#include "Product.h"

int main() {
    spdlog::info("Hello, World!");
    std::string filename = "../data/meta/meta_AMAZON_FASHION.json.gz";
    AmazonProductDataset dataset(filename);

    std::string test_asin = "B005HWMEPK";
    auto product = dataset.getProduct(test_asin);
    if (product.has_value()) {
        spdlog::info("Dataset contains {}", test_asin);
        product.value().printProductInfo();
    } else {
        spdlog::info("Dataset does not contain {}", test_asin);
    }

    return 0;
}
