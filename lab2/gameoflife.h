#pragma once

#include <unordered_set>
#include <QString>
#include "field.h"

class GameOfLife {
public:
    GameOfLife(int rows, int cols);
    void Update();
    void SetRules(std::unordered_set<int> birth_rules, std::unordered_set<int> survival_rules);
    void OfflineMode(int number_of_iterations);
    bool LoadUniverse(std::vector<std::pair<int, int>> alive_cells);
    QString GetRules();
    Field &GetField();
private:
    Field field_;
    std::unordered_set<int> birth_rules_;
    std::unordered_set<int> survival_rules_;
    int CountAliveNeighbors(int row, int col) const;
};
