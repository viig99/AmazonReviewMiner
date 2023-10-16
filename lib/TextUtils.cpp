//
// Created by vigi99 on 10/14/23.
//

#include "TextUtils.h"

string strip(const string& input) {
    auto is_space = [](unsigned char c) { return isspace(c); };
    auto no_newlines = [](unsigned char c) { return c != '\n'; };

    auto trimmed = input | views::drop_while(is_space)
                   | views::reverse
                   | views::drop_while(is_space)
                   | views::reverse
                   | views::filter(no_newlines);
    string result(trimmed.begin(), trimmed.end());

    // Remove consecutive spaces
    auto new_end = unique(result.begin(), result.end(), [](char a, char b) {
        return isspace(a) && isspace(b);
    });

    result.erase(new_end, result.end());
    return result;
}

string join(const vector<string>& vec, const string& delimiter) {
    string result;

    for (size_t i = 0; i < vec.size(); ++i) {
        result += vec[i];
        if (i < vec.size() - 1) { // Don't add delimiter after the last element
            result += delimiter;
        }
    }

    return result;
}

unordered_set<string> split(const string& input, const string& delimiter) {
    unordered_set<string> result;
    size_t start = 0;
    size_t end = input.find(delimiter);
    while (end != string::npos) {
        result.emplace(input.substr(start, end - start));
        start = end + delimiter.length();
        end = input.find(delimiter, start);
    }
    result.emplace(input.substr(start, end));
    return result;
}

string getStringOrDefault(const Document& doc, const string& key, const string& default_value) {
    auto itr = doc.FindMember(key.c_str());
    if (itr != doc.MemberEnd()) {
        return strip(itr->value.GetString());
    }
    return default_value;
}

string getStringFromArrayOrDefault(const Document& doc, const string& key, const string& default_value) {
    auto itr = doc.FindMember(key.c_str());
    string concat_str;
    if (itr != doc.MemberEnd()) {
        for (auto &v : itr->value.GetArray()) {
            concat_str += v.GetString() + ' ';
        }
        return strip(concat_str);
    }
    return default_value;
}

string to_lower(const string& input) {
    string lower;
    transform(input.begin(), input.end(), std::back_inserter(lower), ::tolower);
    return lower;
}

StopwordRemover::StopwordRemover(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        spdlog::error("File {} does not exist", filename);
        return;
    }

    string line;
    while (getline(file, line)) {
        stopwords.emplace(to_lower(line));
    }
    spdlog::info("# Stopwords: {}", stopwords.size());
}

bool StopwordRemover::isStopword(const string &word) {
    auto word_lower = to_lower(word);
    return stopwords.find(word_lower) != stopwords.end();
}

string StopwordRemover::removeStopwords(const string &input) {
    string result;
    istringstream iss(input);
    string word;
    while (iss >> word) {
        if (!isStopword(word)) {
            if (!result.empty())
                result += ' ';
            result += word;
        }
    }
    return result;
}
