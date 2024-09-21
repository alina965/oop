#include "counter.h"
#include <algorithm>

void Counter::Count(string &line) {
    string word;
    for (auto& symbol : line) {
        if (isalpha(symbol) || isdigit(symbol)) word += symbol;
        else {
            if (!word.empty()) {
                num_of_words_ += 1;
                frequency_[word] += 1;
                word = "";
            }
        }
    }
    if (!word.empty()) {
        num_of_words_ += 1;
        frequency_[word] += 1;
    }
}

bool Counter::Compare(const pair<string, int> &a, const pair<string, int> &b) {
    return a.second > b.second;
}

vector<pair<string, int>> Counter::GetSortedFrequency() {
    vector<pair<string, int>> sorted_frequency(frequency_.begin(), frequency_.end());
    sort(sorted_frequency.begin(), sorted_frequency.end(), Compare);
    return sorted_frequency;
}

int Counter::GetNumOfWords() const {
    return num_of_words_;
}