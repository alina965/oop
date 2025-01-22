#pragma once

#include "populator.h"

class RandomPopulator : public IPopulator {
public:
    bool Populate(std::vector<std::pair<int, int>>& alive_cells,
                  std::unordered_set<int>& birth_rules,
                  std::unordered_set<int>& survival_rules) override;
};
