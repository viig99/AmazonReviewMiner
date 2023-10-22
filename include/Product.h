#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <optional>
#include "JSONLReader.h"
#include "TextUtils.h"
#include "TimeUtils.h"

using namespace std;

struct Product {
    string brand;
    string title;
    string description;
    string feature;
    vector<string> also_viewed;
    vector<string> also_buy;

    // Parameterized constructor using constructor delegation
    explicit Product(Document &doc);

    void printProductInfo();
};

class AmazonProductDataset {
public:
    explicit AmazonProductDataset(const string &filename);

    optional<Product> getProduct(const string &asin);

    void showProducts();

private:
    unordered_map<string, Product> asin2product;
};
