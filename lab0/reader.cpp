#include "reader.h"

Reader::Reader(string& filename): input_file_(filename) { }
bool Reader::Read(string& line) {
    if (getline(input_file_, line)) return true;
    return false;
}