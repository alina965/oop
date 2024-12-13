#include "alivecell.h"

AliveCell::AliveCell() : Cell(true) {}

bool AliveCell::IsAlive() const {
    return true;
}
