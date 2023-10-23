//
// Created by vigi99 on 10/15/23.
//

#include "YAKE.h"

vector<vector<string>> YAKE::tokenize(const string &sentence) {
    vector<vector<string>> result;
    auto is_delimiter = [](char c) { return isspace(c) || ispunct(c); };
    auto is_sentence_end = [](char c) { return ispunct(c) || c == '\n'; };
    auto sentence_start = sentence.begin();
    while (sentence_start != sentence.end()) {
        auto sentence_end = find_if(sentence_start, sentence.end(), is_sentence_end);
        vector<string> tokens;
        auto start = sentence_start;
        while (start != sentence_end) {
            auto end = find_if(start, sentence_end, is_delimiter);
            if (start != end)
                tokens.emplace_back(start, end);
            start = (end == sentence_end) ? end : next(end);
        }
        result.push_back(tokens);
        sentence_start = (sentence_end == sentence.end()) ? sentence_end : next(sentence_end);
    }
    return result;
}

void YAKE::updateFrequencies(const string& word, int sentencePosition, const optional<string>& leftWord, const optional<string>& rightWord) {
    if (word.empty()) return;

    string word_lower = to_lower(word);
    PositionW[word_lower].insert(sentencePosition + 1);
    _tf[word_lower] += 1;

    if (isupper(word[0])) {
        _tfU[word_lower] += 1;
    }

    auto is_acronym = all_of(word.begin(), word.end(), ::isupper);
    if (is_acronym) {
        _tfA[word_lower] += 1;
    }

    if (leftWord.has_value()) {
        string leftWord_lower = to_lower(leftWord.value());
        CoOccurrenceLeft[word_lower].insert(leftWord_lower);

        string bigram_lower = leftWord_lower + " " + word_lower;
        _tfBigrams[bigram_lower] += 1;
    }

    if (rightWord.has_value()) {
        string rightWord_lower = to_lower(rightWord.value());
        CoOccurrenceRight[word_lower].insert(rightWord_lower);
    }

    if (leftWord.has_value() && rightWord.has_value()) {
        string trigram_lower = to_lower(leftWord.value()) + " " + word_lower + " " + to_lower(rightWord.value());
        _tfTrigrams[trigram_lower] += 1;
    }


}

double YAKE::scoreWCase(const string& word) {
    string word_lower = to_lower(word);
    int tf = _tf[word_lower];
    int tfU = _tfU[word_lower];
    int tfA = _tfA[word_lower];

    int max_tfU_tfA = max(tfU, tfA);

    if (tf == 0) {
        return 0.0;
    }

    return static_cast<double>(max_tfU_tfA) / log2(1 + tf);
}

double YAKE::scoreWPosition(const string& word) {
    string word_lower = to_lower(word);
    auto sentencePositions = PositionW[word_lower];

    // Handle empty sentencePositions
    if (sentencePositions.empty()) {
        return log2(log2(2)); // The equation simplified for medianOfSentences = 0
    }

    // Calculate the median
    auto sentencePosVec = vector<int>(sentencePositions.begin(), sentencePositions.end());
    auto medianOfSentences = median(sentencePosVec);

    return log2(log2(2 + medianOfSentences));
}

double YAKE::scoreWFrequency(const string& word ) {
    string word_lower = to_lower(word);
    int tf = _tf[word_lower];

    if (tf == 0) {
        return 0.0;
    }

    return static_cast<double>(tf) / (_meanTF + _stdDevTF);
}

double YAKE::scoreWRelatedness(const string& word) {
    string word_lower = to_lower(word);
    if (_stopwordRemover->isStopword(word_lower)) {
        return stopWordRel;
    }

    auto freq = _tf[word_lower] / _maxTF;
    auto totalCoOccurrence = unionSize(CoOccurrenceLeft[word_lower], CoOccurrenceRight[word_lower]);
    auto WL = (double)CoOccurrenceLeft[word_lower].size() / (double)totalCoOccurrence;
    auto WR = (double)CoOccurrenceRight[word_lower].size() / (double)totalCoOccurrence;
    auto PL = (double)CoOccurrenceLeft[word_lower].size() / _maxTF;
    auto PR = (double)CoOccurrenceRight[word_lower].size() / _maxTF;

    return (0.5 + (WL * freq) + PL) + (0.5 + (WR * freq) + PR);
}

double YAKE::scoreWDiffSentence(const string& word) {
    string word_lower = to_lower(word);
    auto sentencePositions = PositionW[word_lower];
    auto sentenceFreq = sentencePositions.size();
    return static_cast<double>(sentenceFreq) / static_cast<double>(_numSentences);
}

double YAKE::scoreTerm(const string& word) {
    double scoreCase = scoreWCase(word);
    double scorePosition = scoreWPosition(word);
    double scoreFrequency = scoreWFrequency(word);
    double scoreDiffSentence = scoreWDiffSentence(word);
    double scoreRelatedness = scoreWRelatedness(word);

    double numerator = scoreRelatedness * scorePosition;
    double denominator = scoreCase + (scoreFrequency/scoreRelatedness) + (scoreDiffSentence/scoreRelatedness);
    return numerator / denominator;
}

double YAKE::scoreCandidateKeywords(const string& word) {
    string word_lower = to_lower(word);
    auto tokens = split(word, " ");
    auto numTokens = tokens.size();
    int termFreq;
    if (numTokens == 1) {
        termFreq = _tf[word_lower];
    } else if (numTokens == 2) {
        termFreq = _tfBigrams[word_lower];
    } else if (numTokens == 3) {
        termFreq = _tfTrigrams[word_lower];
    } else {
        throw invalid_argument("Unsupported number of tokens in " + word);
    }

    auto transformed_range = tokens |
            views::transform([&](const string& token) { return scoreTerm(token); });
    auto productNum = accumulate(transformed_range.begin(), transformed_range.end(), 1.0, multiplies<>());
    auto sumDenom = accumulate(transformed_range.begin(), transformed_range.end(), 0.0, plus<>());

    return productNum / ((1.0 + sumDenom) * static_cast<double>(termFreq));
}

YAKE::YAKE(const string &sentence) {
    Timer timer("YAKE mainFunc");
    _stopwordRemover = make_unique<StopwordRemover>("../assets/stopwords-en.txt");

    auto sentences = tokenize(sentence);
    _numSentences = (int)sentences.size();

    for (int i = 0; i < _numSentences; i++) {
        auto tokens = sentences[i];
        for (int j = 0; j < tokens.size(); j++) {
            auto word = tokens[j];
            auto leftWord = (j == 0) ? optional<string>() : optional<string>(tokens[j-1]);
            auto rightWord = (j == tokens.size() - 1) ? optional<string>() : optional<string>(tokens[j+1]);
            updateFrequencies(word, i, leftWord, rightWord);
        }
    }

    auto res = mean_max_std(_tf);
    _meanTF = get<0>(res);
    _maxTF = get<1>(res);
    _stdDevTF = get<2>(res);

    //    The final step in determining suitable candidate keywords is to eliminate
    //    similar candidates. For this, we use the Levenshtein distance [4] which measures the
    //    similarity between two strings. Among the strings considered similar (in our case, two
    //    strings are considered similar if their Levenshtein distance is above a given threshold)
    //    we keep the one that has the lowest S(kw) score. Finally, the method will output a list
    //    of potential relevant keywords, formed by 1, 2 or 3-g, such that the lower the S(kw
    //    score the more important the keyword will be.
    auto keywords = generateCandidateKeywords(sentences);

    for (const auto& kw : keywords) {
        cout << kw.first << ":" << kw.second << endl;
    }

}

vector<pair<string, double>> YAKE::generateCandidateKeywords(const vector<vector<string>>& sentences) {
    for (int i = 0; i < _numSentences; i++) {
        auto tokens = sentences[i];
        for (int j = 0; j < tokens.size(); j++) {
            auto word = tokens[j];
            auto leftWord = (j == 0) ? optional<string>() : optional<string>(tokens[j-1]);
            auto rightWord = (j == tokens.size() - 1) ? optional<string>() : optional<string>(tokens[j+1]);

            if (!_nGramScores.contains(word) and !_stopwordRemover->isStopword(word)) {
                _nGramScores[word] = scoreCandidateKeywords(word);
            }

            if (leftWord.has_value()) {
                auto bigram = leftWord.value() + " " + word;
                if (!_nGramScores.contains(bigram) and !_stopwordRemover->containsStopword(bigram)) {
                    _nGramScores[bigram] = scoreCandidateKeywords(bigram);
                }
            }

            if (leftWord.has_value() && rightWord.has_value()) {
                auto trigram = leftWord.value() + " " + word + " " + rightWord.value();
                if (!_nGramScores.contains(trigram)) {
                    _nGramScores[trigram] = scoreCandidateKeywords(trigram);
                }
            }

        }
    }

    // Create a vector of pairs (key, value) from _nGramScores
    vector<pair<string, double>> keyValuePairs(_nGramScores.begin(), _nGramScores.end());

    // Sort the keyValuePairs by value in ascending order
    sort(keyValuePairs.begin(), keyValuePairs.end(),
              [](const auto& a, const auto& b) {
                  return a.second < b.second;
              });

    return keyValuePairs;
}
