#pragma once

#include <vector>
#include <memory>
#include "cell.h"

class Field {
public:
    Field(int rows, int cols);
    void ResizeGrid(int new_rows, int new_cols);
    void ToggleCellState(int row, int col);
    const std::unique_ptr<Cell>& GetCell(int row, int col) const;
    int GetRows() const;
    int GetCols() const;
private:
    int rows_;
    int cols_;
    std::vector<std::vector<std::unique_ptr<Cell>>> grid_;
};
