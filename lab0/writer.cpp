#include "writer.h"

Writer::Writer(string& filename): output_file_(filename) { }
void Writer::Write(vector<pair<string, int>>& sorted_frequency, int num_of_words) {
    for (auto& element : sorted_frequency) {
        output_file_ << element.first << "," << element.second << "," << ((element.second / (float)num_of_words) * 100) << endl;
    }
}