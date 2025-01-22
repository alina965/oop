#pragma once

#include "populator.h"
#include <QString>

class FilePopulator : public IPopulator{
public:
    FilePopulator(const QString& filename);
    bool Populate(std::vector<std::pair<int, int>>& alive_cells,
                  std::unordered_set<int>& birth_rules,
                  std::unordered_set<int>& survival_rules) override;
private:
    QString filename_;
};
