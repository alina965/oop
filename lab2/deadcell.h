#pragma once

#include "cell.h"

class DeadCell : public Cell {
public:
    DeadCell();
    bool IsAlive() const override;
};
