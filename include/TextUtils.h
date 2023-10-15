//
// Created by vigi99 on 10/14/23.
//

#pragma once

#include <string>
#include <algorithm>
#include <cctype>
#include <ranges>
#include <iostream>
#include <spdlog/spdlog.h>
#include <rapidjson/document.h>

using namespace std;
using namespace rapidjson;

string trimLower(const string& input);
string join(const vector<string>& vec, const string& delimiter);

string getStringOrDefault(const Document& doc, const string& key, const string& default_value = "");
string getStringFromArrayOrDefault(const Document& doc, const string& key, const string& default_value = "");