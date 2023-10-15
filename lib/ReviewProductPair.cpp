//
// Created by vigi99 on 10/15/23.
//

#include "ReviewProductPair.h"

bool ReviewProductPairProcessor::review_contains_product_metadata(const Review& review, const Product& product) {
    if (product.brand.empty())
        return false;

    auto stop_word_remove_and_lower = [&](const auto& text) { return to_lower(_stopwordRemover->removeStopwords(text)); };

    auto review_text = stop_word_remove_and_lower(review.title + " " + review.message);
    auto brand_keywords = split(stop_word_remove_and_lower(product.brand));

    auto keyword_in_review_text = [&review_text](auto& keyword) { return review_text.find(keyword) != std::string::npos; };

    if (brand_keywords.empty() or !ranges::any_of(brand_keywords, keyword_in_review_text))
        return false;

    auto product_text = stop_word_remove_and_lower(product.title + " " + product.description + " " + product.feature);
    auto product_keywords = split(product_text);

    return ranges::any_of(product_keywords, keyword_in_review_text);
}