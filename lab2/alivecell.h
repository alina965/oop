#pragma once

#include "cell.h"

class AliveCell : public Cell {
public:
    AliveCell();
    bool IsAlive() const override;
};
