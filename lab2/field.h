#pragma once

#include <vector>
#include <memory>
#include "cell.h"
#include "cellfactory.h"
#include <string>

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
    CellFactory<Cell, std::string, std::function<std::unique_ptr<Cell>()>> factory_;
};
