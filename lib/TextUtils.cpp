//
// Created by vigi99 on 10/14/23.
//

#include "TextUtils.h"

string trim(const string& input) {
    string str = input;
    auto newEnd = unique(str.begin(), str.end(), [](char a, char b) {
        return isspace(a) && isspace(b) && a == b;
    });
    str.erase(newEnd, str.end());
    str.erase(remove(str.begin(), str.end(), '\n'), str.end());
    return str;
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