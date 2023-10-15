//
// Created by vigi99 on 10/15/23.
//

#include "Utils.h"

string glob_to_regex(const string& glob) {
    string regex;
    for (char c : glob) {
        switch (c) {
            case '*': regex += ".*"; break;
            case '?': regex += "."; break;
            case '.': regex += "\\."; break;
            default: regex += c; break;
        }
    }
    return regex;
}

vector<fs::path> glob(const fs::path& pattern) {
    vector<fs::path> result;
    regex re(glob_to_regex(pattern.filename().string()));

    for (const auto& p : fs::directory_iterator(pattern.parent_path())) {
        if (fs::is_regular_file(p) && regex_match(p.path().filename().string(), re)) {
            result.push_back(p);
        }
    }

    // Sort the result vector based on the filenames.
    sort(result.begin(), result.end(), [](const fs::path& a, const fs::path& b) {
        return a.filename().string() < b.filename().string();
    });
    return result;
}

vector<tuple<fs::path, fs::path>> zip(
        const vector<fs::path>& a,
        const vector<fs::path>& b
) {
    vector<tuple<fs::path, fs::path>> zipped;
    auto size = min(a.size(), b.size());
    zipped.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        zipped.emplace_back(a[i], b[i]);
    }
    return zipped;
}