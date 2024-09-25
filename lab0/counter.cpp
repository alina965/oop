#include "counter.h"
#include <algorithm>

void Counter::Count(std::string &line) {
    std::string word;
    for (auto& symbol : line) {
        if (isalpha(symbol) || isdigit(symbol)) word += symbol;
        else if (!word.empty()) {
                num_of_words_++;
                frequency_[word]++;
                word = "";
        }
    }
    if (!word.empty()) {
        num_of_words_++;
        frequency_[word]++;
    }
}

std::vector<std::pair<std::string, int>> Counter::GetSortedFrequency() {
    std::vector<std::pair<std::string, int>> sorted_frequency(frequency_.begin(), frequency_.end());
    sort(sorted_frequency.begin(), sorted_frequency.end(), [](const auto &a, const auto &b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second > b.second;
    });

    return sorted_frequency;
}

int Counter::GetNumOfWords() const {
    return num_of_words_;
}
