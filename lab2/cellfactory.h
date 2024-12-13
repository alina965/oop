#pragma once

#include <memory>
#include "cell.h"

class CellFactory {
public:
    static std::unique_ptr<Cell> CreateCell(bool alive);
};
