#include "cellfactory.h"
#include "alivecell.h"
#include "deadcell.h"

std::unique_ptr<Cell> CellFactory::CreateCell(bool alive) {
    if (alive) {
        return std::make_unique<AliveCell>();
    }
    else {
        return std::make_unique<DeadCell>();
    }
}
