#pragma once
#include <string>
#include <fstream>
#include <vector>

class Writer {
 public:
    Writer(std::string& filename);
    ~Writer();
    void Write(std::vector<std::pair<std::string, int>>& sorted_frequency, int num_of_words);
 private:
    std::ofstream output_file_;
};
