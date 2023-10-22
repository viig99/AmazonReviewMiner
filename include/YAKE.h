//
// Created by vigi99 on 10/15/23.
//

#pragma once

#include "string"
#include "vector"
#include "algorithm"
#include "unordered_map"
#include "unordered_set"
#include "TextUtils.h"
#include "Utils.h"
#include "TimeUtils.h"

using namespace std;

class YAKE {
public:
    explicit YAKE(const string &sentence);

private:
    static vector<vector<string>> tokenize(const string &sentence);

    void updateFrequencies(const string &word, int sentencePosition, const optional<string> &leftWord,
                           const optional<string> &rightWord);

    double scoreWCase(const string &word);
    double scoreWPosition(const string &word);
    double scoreWFrequency(const string &word);
    double scoreWRelatedness(const string &word);
    double scoreWDiffSentence(const string &word);
    double scoreTerm(const string &word);
    double scoreCandidateKeywords(const string &word);

    vector<string> generateCandidateKeywords(const vector<vector<string>> &sentences);

    // Internal Stats Tracking
    unordered_map<string, int> _tfU;
    unordered_map<string, int> _tfA;
    unordered_map<string, unordered_set<int>> PositionW;
    unordered_map<string, unordered_set<string>> CoOccurrenceLeft;
    unordered_map<string, unordered_set<string>> CoOccurrenceRight;

    unordered_map<string, int> _tf;
    unordered_map<string, int> _tfBigrams;
    unordered_map<string, int> _tfTrigrams;
    unordered_map<string, double> _nGramScores;

    // Utils
    unique_ptr<StopwordRemover> _stopwordRemover;

    // Compute aggregated stats
    double _meanTF;
    double _maxTF;
    double _stdDevTF;
    int _numSentences;
    const double stopWordRel = 5.0;
    const int maxNgrams = 3;
};
