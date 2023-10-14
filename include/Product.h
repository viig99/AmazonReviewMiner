#pragma once

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <optional>
#include "JSONLReader.h"
#include "TextUtils.h"
#include "TimeUtils.h"

using namespace std;

string getStringOrDefault(const Document& doc, const string& key, const string& default_value = "");
string getStringFromArrayOrDefault(const Document& doc, const string& key, const string& default_value = "");

struct Product {
    string brand;
    string title;
    string description;
    string feature;
    vector<string> also_viewed;
    vector<string> also_buy;

    // Parameterized constructor using constructor delegation
    explicit Product(Document & doc);
    void printProductInfo();
};

class AmazonProductDataset {
public:
    explicit AmazonProductDataset(const string& filename);
    optional<Product> getProduct(const string& asin);
    void showProducts();

private:
    unordered_map<string, Product> asin2product;
};
