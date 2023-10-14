//
// Created by vigi99 on 10/14/23.
//

#pragma once

#include <string>
#include <algorithm>
#include <cctype>
#include <ranges>
#include <iostream>
#include "spdlog/spdlog.h"

using namespace std;
string trimLower(const string& input);
string join(const vector<string>& vec, const string& delimiter);