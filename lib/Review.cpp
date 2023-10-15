//
// Created by vigi99 on 10/15/23.
//

#include "Review.h"

Review::Review(Document & doc) {
    product_id = doc["asin"].GetString();
    message = getStringOrDefault(doc, "reviewText");
    title = getStringOrDefault(doc, "summary");
}

void Review::printReviewInfo() {
    spdlog::info("Product ID: {}", product_id);
    spdlog::info("Title: {}", title);
    spdlog::info("Message: {}", message);
}

coro::generator<Review> AmazonReviewDataset::generate(const string& filename ) {
    for (auto& doc : JSONLReader::generate(filename)) {
        co_yield Review(doc);
    }
}