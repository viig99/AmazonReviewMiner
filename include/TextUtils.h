//
// Created by vigi99 on 10/14/23.
//

#pragma once

#include <string>
#include <algorithm>
#include <cctype>
#include <ranges>
#include <iostream>
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>
#include <rapidjson/document.h>
#include <unordered_set>

using namespace std;
using namespace rapidjson;

string trimLower(const string& input);
string join(const vector<string>& vec, const string& delimiter);
string to_lower(const string& input);
unordered_set<string> split(const string& input, const string& delimiter = " ");

string getStringOrDefault(const Document& doc, const string& key, const string& default_value = "");
string getStringFromArrayOrDefault(const Document& doc, const string& key, const string& default_value = "");

class StopwordRemover {
    public:
        StopwordRemover(const string& filename);
        bool isStopword(const string& word);
        string removeStopwords(const string& input);
    private:
        unordered_set<string> stopwords;
};