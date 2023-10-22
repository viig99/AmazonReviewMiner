//
// Created by vigi99 on 10/15/23.
//

#pragma once

#include <string>
#include "JSONLReader.h"
#include "TextUtils.h"
#include "TimeUtils.h"
#include <coro/coro.hpp>

using namespace std;

struct Review {
    string product_id;
    string message;
    string title;

    // Parameterized constructor using constructor delegation
    explicit Review(Document &doc);

    void printReviewInfo();
};

class AmazonReviewDataset {
public:
    static coro::generator<Review> generate(const string &filename);
};

