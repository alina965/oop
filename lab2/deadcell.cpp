#include "deadcell.h"

DeadCell::DeadCell() : Cell(false) {}

bool DeadCell::IsAlive() const {
    return false;
}
