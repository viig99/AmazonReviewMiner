//
// Created by vigi99 on 10/14/23.
//

#include "Product.h"

Product::Product(const json& j) {
    brand = j.value("brand", "");
    title = j.value("title", "");

    if (j.contains("description")) {
        for (const auto &d: j["description"]) {
            description += d.get<string>() + " ";
        }
    }

    if (j.contains("feature")) {
        for (const auto &f: j["feature"]) {
            feature += f.get<string>() + " ";
        }
    }

    if (j.contains("also_viewed")) {
        for (const auto &asin: j["also_viewed"]) {
            also_viewed.emplace_back(asin.get<string>());
        }
    }

    if (j.contains("also_buy")) {
        for (const auto &asin: j["also_buy"]) {
            also_buy.emplace_back(asin.get<string>());
        }
    }
}

AmazonProductDataset::AmazonProductDataset(const string& filename) {
    if (!filesystem::exists(filename)) {
        spdlog::error("File {} does not exist", filename);
        return;
    }

    spdlog::info("Loading dataset from {}", filename);
    for (const auto& j : JSONLReader::generate(filename)) {
        asin2product.emplace(j["asin"].get<string>(), Product(j));
    }
    spdlog::info("Loaded {} products", asin2product.size());
}

Product AmazonProductDataset::getProduct(const string &asin) {
    return asin2product.at(asin);
}

bool AmazonProductDataset::hasProduct(const string &asin) {
    return asin2product.contains(asin);
}
