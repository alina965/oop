#ifndef READER_H_
#define READER_H_
#include <string>
#include <fstream>
using namespace std;

class Reader {
public:
    Reader(string& filename);
    bool Read(string& line);
private:
    ifstream input_file_;
};
#endif // READER_H_
