//
// Created by vigi99 on 10/15/23.
//

#include "ReviewProductPair.h"

bool ReviewProductPairProcessor::review_contains_product_metadata(const Review& review, const Product& product) {
    if (product.brand.empty())
        return false;

    auto removeStopwords = [&](const auto& text) { return _stopwordRemover->removeStopwords(text); };

    auto review_text = removeStopwords(review.title + " " + review.message);
    auto brand_keywords = split(removeStopwords(product.brand));

    auto keyword_in_review_text = [&review_text](auto& keyword) { return review_text.find(to_lower(keyword)) != std::string::npos; };

    if (brand_keywords.empty() or !ranges::any_of(brand_keywords, keyword_in_review_text))
        return false;

    auto product_text = removeStopwords(product.title + " " + product.description + " " + product.feature);
    auto product_keywords = split(product_text);

    return ranges::any_of(product_keywords, keyword_in_review_text);
}