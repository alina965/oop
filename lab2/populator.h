#pragma once

#include <vector>
#include <unordered_set>

class IPopulator {
public:
    virtual ~IPopulator() = default;
    virtual bool Populate(std::vector<std::pair<int, int>>& alive_cells,
                          std::unordered_set<int>& birth_rules,
                          std::unordered_set<int>& survival_rules) = 0;
};
