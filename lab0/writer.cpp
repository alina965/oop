#include "writer.h"

Writer::Writer(std::string& filename): output_file_(filename) { }

Writer::~Writer() {
    output_file_.close();
}

void Writer::Write(std::vector<std::pair<std::string, int>>& sorted_frequency, int num_of_words) {
    for (auto& element : sorted_frequency) {
        output_file_ << element.first << "," << element.second << "," << ((element.second / static_cast<float>(num_of_words)) * 100) << std::endl;
    }
}
