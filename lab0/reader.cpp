#include "reader.h"

Reader::Reader(std::string& filename): input_file_(filename) { }

Reader::~Reader() {
    input_file_.close();
}

bool Reader::Read(std::string& line) {
    return static_cast<bool>(getline(input_file_, line));
}
