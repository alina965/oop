#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "reader.h"
#include "counter.h"
#include "writer.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) return 0;
    string input_file = argv[1];
    string output_file = argv[2];
    ifstream in(input_file);
    ofstream out(output_file);
    Reader reader(input_file);
    Counter counter;
    Writer writer(output_file);
    string line;
    while (reader.Read(line)) {
        counter.Count(line);
    }
    int num_of_words = counter.GetNumOfWords();
    vector<pair<string, int>> sorted_frequency = counter.GetSortedFrequency();
    writer.Write(sorted_frequency, num_of_words);
    in.close();
    out.close();
    return 0;
}