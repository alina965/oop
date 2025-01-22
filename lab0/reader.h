#pragma once
#include <string>
#include <fstream>

class Reader {
 public:
    Reader(std::string& filename);
    ~Reader();
    bool Read(std::string& line);
 private:
    std::ifstream input_file_;
};
