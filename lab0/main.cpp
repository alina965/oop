#include <string>
#include <map>
#include <vector>
#include "reader.h"
#include "counter.h"
#include "writer.h"

int main(int argc, char* argv[]) {
    if (argc != 3) return 0;

    std::string input_file = argv[1];
    std::string output_file = argv[2];

    Reader reader(input_file);
    Counter counter;
    Writer writer(output_file);

    std::string line;
    while (reader.Read(line)) {
        counter.Count(line);
    }
    int num_of_words = counter.GetNumOfWords();
    std::vector<std::pair<std::string, int>> sorted_frequency = counter.GetSortedFrequency();
    writer.Write(sorted_frequency, num_of_words);
    return 0;
}
