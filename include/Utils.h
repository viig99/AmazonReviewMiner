//
// Created by vigi99 on 10/15/23.
//

#pragma once

#include <regex>
#include <iostream>
#include <vector>
#include <filesystem>
#include <ranges>
#include <numeric>
#include <cmath>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>

using namespace std;
namespace fs = filesystem;

string glob_to_regex(const string &glob);

vector<fs::path> glob(const fs::path &pattern);

vector<tuple<fs::path, fs::path>> zip(
        const vector<fs::path> &a,
        const vector<fs::path> &b
);

template<typename T>
T median(vector<T> vec) {
    size_t n = vec.size() / 2;
    nth_element(vec.begin(), vec.begin() + n, vec.end());
    return vec[vec.size() / 2];
}

template<typename T>
tuple<double, double, double> mean_max_std(const unordered_map<string, T> &map) {
    if (map.empty()) {
        return {0.0, T{}, 0.0}; // return zero for all stats
    }

    auto value_view = map | views::values;

    // Calculate mean
    T sum = accumulate(value_view.begin(), value_view.end(), T{});
    auto size = static_cast<double>(map.size());
    double mean = static_cast<double>(sum) / size;

    // Calculate max
    T max_val = *max_element(value_view.begin(), value_view.end());

    // Calculate standard deviation
    double squared_sum = accumulate(value_view.begin(), value_view.end(), 0.0, [mean](double acc, T val) {
        return acc + pow(val - mean, 2);
    });
    double std_dev = sqrt(squared_sum / size);

    return {mean, static_cast<double>(max_val), std_dev};
}

template<typename T>
int unionSize(const unordered_set<T> &set1, const unordered_set<T> &set2) {
    unordered_set<T> result = set1;  // Copy elements from set1 into result

    // Insert elements from set2 into result. Duplicates will be ignored.
    result.insert(set2.begin(), set2.end());

    // Return the size of the union set
    return (int) result.size();
}


