#ifndef WRITER_H_
#define WRITER_H_
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Writer {
public:
    Writer(string& filename);
    void Write(vector<pair<string, int>>& sorted_frequency, int num_of_words);
private:
    ofstream output_file_;
};
#endif // WRITER_H_