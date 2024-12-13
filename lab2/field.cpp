#include "field.h"
#include "cellfactory.h"

Field::Field(int rows, int cols) : rows_(rows), cols_(cols) {
    grid_.resize(rows_);
    for (int i = 0; i < rows_; i++) {
        grid_[i].resize(cols_);
        for (int j = 0; j < cols_; j++) {
            grid_[i][j] = CellFactory::CreateCell(false);
        }
    }
}

void Field::ResizeGrid(int new_rows, int new_cols) {
    grid_.resize(new_rows);
    for (int i = 0; i < new_rows; i++) {
        grid_[i].resize(new_cols);
        for (int j = 0; j < new_cols; j++) {
            grid_[i][j] = CellFactory::CreateCell(false);
        }
    }
    rows_ = new_rows;
    cols_ = new_cols;
}

void Field::ToggleCellState(int row, int col) {
    if (GetCell(row, col)->IsAlive()) {
        grid_[row][col] = CellFactory::CreateCell(false);
    }
    else {
        grid_[row][col] = CellFactory::CreateCell(true);
    }
}

const std::unique_ptr<Cell> &Field::GetCell(int row, int col) const {
    return grid_[row][col];
}

int Field::GetRows() const {
    return rows_;
}

int Field::GetCols() const {
    return cols_;
}
