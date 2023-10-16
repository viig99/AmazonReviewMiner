#include "spdlog/spdlog.h"
#include "Product.h"
#include "Review.h"
#include "TimeUtils.h"
#include "Utils.h"
#include "ReviewProductPair.h"

int main() {
    auto metadata_filenames = glob("../data/meta/*.json.gz");
    auto review_filenames = glob("../data/reviews/*.json.gz");

    auto paired_filenames = zip(metadata_filenames, review_filenames);
    auto processor = ReviewProductPairProcessor();

    for (const auto& [metadata_filename_path, review_filename_path] : paired_filenames) {
        auto metadata_filename = metadata_filename_path.relative_path().string();
        auto review_filename = review_filename_path.relative_path().string();
        spdlog::info("Metadata: {}, Review: {}", metadata_filename, review_filename);
        Timer timer("Product Review Pairs");
        AmazonProductDataset dataset(metadata_filename);
        int num_reviews_with_condition = 0;
        int num_reviews = 0;

        for (auto& review : AmazonReviewDataset::generate(review_filename)) {
            auto product_o = dataset.getProduct(review.product_id);
            if (product_o.has_value()) {
                auto product = product_o.value();
                if (processor.review_contains_product_metadata(review, product)) {
                    num_reviews_with_condition++;
                }
            }
            num_reviews++;
        }

        spdlog::info("# Reviews with product metadata: {}", num_reviews_with_condition);
        spdlog::info("# Reviews: {}", num_reviews);
    }

    return 0;
}
