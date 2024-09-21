#ifndef COUNTER_H_
#define COUNTER_H_
#include <string>
#include <map>
#include <vector>
using namespace std;

class Counter {
public:
    void Count(string &line);
    static bool Compare(const pair<string, int> &a, const pair<string, int> &b);
    vector<pair<string, int>> GetSortedFrequency();
    int GetNumOfWords() const;
private:
    int num_of_words_ = 0;
    map<string, int> frequency_;
};
#endif // COUNTER_H_