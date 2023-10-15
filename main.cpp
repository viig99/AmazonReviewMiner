#include "spdlog/spdlog.h"
#include "Product.h"
#include "Review.h"

int main() {
    std::string metadata_filename = "../data/meta/meta_AMAZON_FASHION.json.gz";
    std::string review_filename = "../data/reviews/AMAZON_FASHION_5.json.gz";

    AmazonProductDataset dataset(metadata_filename);
    for (auto review : AmazonReviewDataset::generate(review_filename)) {
        review.printReviewInfo();
        auto product_o = dataset.getProduct(review.product_id);
        if (product_o.has_value()) {
            auto product = product_o.value();
            product.printProductInfo();
        }
        break;
    }

    return 0;
}
