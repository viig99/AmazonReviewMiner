//
// Created by vigi99 on 10/15/23.
//

#pragma once
#include "Product.h"
#include "Review.h"
#include "string"
#include "TextUtils.h"

class ReviewProductPairProcessor {
public:
    ReviewProductPairProcessor() {
        _stopwordRemover = std::make_unique<StopwordRemover>("../assets/stopwords-en.txt");
    }
    bool review_contains_product_metadata(const Review& review, const Product& product);

private:
    std::unique_ptr<StopwordRemover> _stopwordRemover;
};
