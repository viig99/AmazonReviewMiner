#pragma once

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "JSONLReader.h"

using namespace std;

struct Product {
    string brand;
    string title;
    string description;
    string feature;
    vector<string> also_viewed;
    vector<string> also_buy;

    // Parameterized constructor using constructor delegation
    explicit Product(const json& j);
};

class AmazonProductDataset {
public:
    explicit AmazonProductDataset(const string& filename);
    Product getProduct(const string& asin);
    bool hasProduct(const string& asin);

private:
    unordered_map<string, Product> asin2product;
};
