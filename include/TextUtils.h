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
#include <tsl/hopscotch_set.h>

using namespace std;
using namespace rapidjson;

string strip(const string &input);
string join(const vector<string> &vec, const string &delimiter);
string to_lower(const string &input);
tsl::hopscotch_set<string> split(const string &input, const string &delimiter = " ");

string getStringOrDefault(const Document &doc, const string &key, const string &default_value = "");
string getStringFromArrayOrDefault(const Document &doc, const string &key, const string &default_value = "");

class StopwordRemover {
public:
    explicit StopwordRemover(const string &filename);
    bool isStopword(const string &word);
    bool containsStopword(const string &sentence);
    string removeStopwords(const string &input);

private:
    tsl::hopscotch_set<string> stopwords;
};