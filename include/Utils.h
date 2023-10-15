//
// Created by vigi99 on 10/15/23.
//

#pragma once

#include <regex>
#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

string glob_to_regex(const string& glob);
vector<fs::path> glob(const fs::path& pattern);
vector<tuple<fs::path, fs::path>> zip(
        const vector<fs::path>& a,
        const vector<fs::path>& b
);


