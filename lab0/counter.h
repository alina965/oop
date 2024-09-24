#pragma once
#include <string>
#include <map>
#include <vector>

class Counter {
 public:
    void Count(std::string &line);
    std::vector<std::pair<std::string, int>> GetSortedFrequency();
    int GetNumOfWords() const;
 private:
    int num_of_words_ = 0;
    std::map<std::string, int> frequency_;
};
