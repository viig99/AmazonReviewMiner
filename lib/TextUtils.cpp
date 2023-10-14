//
// Created by vigi99 on 10/14/23.
//

#include "TextUtils.h"

string trimLower(const string& input) {
    auto is_space = [](unsigned char c) { return isspace(c); };
    auto no_newlines = [](unsigned char c) { return c != '\n'; };
    auto to_lower = [](unsigned char c) { return tolower(c); };

    auto trimmed = input | views::drop_while(is_space)
                   | views::reverse
                   | views::drop_while(is_space)
                   | views::reverse
                   | views::transform(to_lower)
                   | views::filter(no_newlines);
    string result(trimmed.begin(), trimmed.end());

    // Remove consecutive spaces
    auto new_end = unique(result.begin(), result.end(), [&is_space](char a, char b) {
        return is_space(a) && is_space(b);
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