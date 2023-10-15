//
// Created by vigi99 on 10/14/23.
//

#include "Product.h"



Product::Product(Document & doc) {
    brand = getStringOrDefault(doc, "brand");
    title = getStringOrDefault(doc, "title");

    description = getStringFromArrayOrDefault(doc, "description");
    feature = getStringFromArrayOrDefault(doc, "feature");

    auto itr_av = doc.FindMember("also_viewed");
    if (itr_av != doc.MemberEnd()) {
        for (auto &v : itr_av->value.GetArray()) {
            also_viewed.emplace_back(v.GetString());
        }
    }

    auto itr_ab = doc.FindMember("also_buy");
    if (itr_ab != doc.MemberEnd()) {
        for (auto &v : itr_ab->value.GetArray()) {
            also_buy.emplace_back(v.GetString());
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
    for (auto& doc : JSONLReader::generate(filename)) {
        asin2product.emplace(doc["asin"].GetString(), Product(doc));
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
