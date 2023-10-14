//
// Created by vigi99 on 10/14/23.
//

#include "Product.h"

Product::Product(const json& j) {
    brand = trim(j.value("brand", ""));
    title = trim(j.value("title", ""));

    if (j.contains("description")) {
        for (const auto &d: j["description"]) {
            description += d.get<string>() + " ";
        }
        description = trim(description);
    }

    if (j.contains("feature")) {
        for (const auto &f: j["feature"]) {
            feature += f.get<string>() + " ";
        }
        feature = trim(feature);
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

void Product::printProductInfo() {
    spdlog::info("Brand: {}", brand);
    spdlog::info("Title: {}", title);
    spdlog::info("Description: {}", description);
    spdlog::info("Feature: {}", feature);
    spdlog::info("Also viewed: {}", fmt::join(also_viewed, ", "));
    spdlog::info("Also buy: {}", fmt::join(also_buy, ", "));
}

AmazonProductDataset::AmazonProductDataset(const string& filename) {
    Timer timer("Loading AmazonProductDataset from JSONL file");
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

optional<Product> AmazonProductDataset::getProduct(const string &asin) {
    auto it = asin2product.find(asin);
    if (it != asin2product.end()) {
        return it->second;  // Return Product if found
    }
    return nullopt;
}

void AmazonProductDataset::showProducts() {
    auto products = asin2product | std::views::keys;
    spdlog::info("Products: {}", fmt::join(products, ", "));
}
