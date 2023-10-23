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
#include <tsl/hopscotch_map.h>
#include <algorithm>
#include <tsl/hopscotch_set.h>

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
    size_t size = vec.size();
    // Check for empty vector
    if (size == 0) {
        throw invalid_argument("Vector is empty, median is undefined.");
    }
    // Calculate index for middle element
    size_t n = size / 2;
    // Partition vector around middle element
    nth_element(vec.begin(), vec.begin() + n, vec.end());

    // If odd size, return the middle element
    if (size % 2 != 0) {
        return vec[n];
    }

    // If even size, find the second middle element and return the average
    T first_middle = vec[n];
    nth_element(vec.begin(), vec.begin() + n - 1, vec.end());
    T second_middle = vec[n - 1];
    return (first_middle + second_middle) / static_cast<T>(2);
}

template<typename T>
tuple<double, double, double> mean_max_std(const tsl::hopscotch_map<string, T> &map) {
    if (map.empty()) {
        return {0.0, T{}, 0.0}; // return zero for all stats
    }

    auto value_view = map | views::values;

    // Calculate mean
    auto sum = accumulate(value_view.begin(), value_view.end(), T{});
    auto size = static_cast<double>(map.size());
    auto mean = static_cast<double>(sum) / size;

    // Calculate max
    auto max_val = *max_element(value_view.begin(), value_view.end());

    // Calculate standard deviation
    auto squared_sum = accumulate(value_view.begin(), value_view.end(), 0.0, [mean](double acc, auto val) {
        return acc + pow(val - mean, 2);
    });
    auto std_dev = sqrt(squared_sum / size);

    return {mean, static_cast<double>(max_val), std_dev};
}

template<typename T>
int unionSize(const tsl::hopscotch_set<T> &set1, const tsl::hopscotch_set<T> &set2) {
    auto result = set1;  // Copy elements from set1 into result

    // Insert elements from set2 into result. Duplicates will be ignored.
    result.insert(set2.begin(), set2.end());

    // Return the size of the union set
    return (int) result.size();
}


