#include "gameoflife.h"
#include <vector>

GameOfLife::GameOfLife(int rows, int cols) : field_(rows, cols), birth_rules_({3}), survival_rules_({2, 3}) {}

void GameOfLife::Update() {
    Field new_field(field_.GetRows(), field_.GetCols());

    int rows = field_.GetRows();
    int cols = field_.GetCols();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int alive_neighbors = CountAliveNeighbors(i, j);
            bool is_alive = field_.GetCell(i, j)->IsAlive();

            if (is_alive && (survival_rules_.find(alive_neighbors) != survival_rules_.end())) {
                new_field.ToggleCellState(i, j); // клетка остается живой
            }

            else if (!is_alive && birth_rules_.find(alive_neighbors) != birth_rules_.end()) {
                new_field.ToggleCellState(i, j); // оживляем клетку
            }
        }
    }

    field_ = std::move(new_field);
}

void GameOfLife::SetRules(std::unordered_set<int> birth_rules, std::unordered_set<int> survival_rules) {
    birth_rules_ = birth_rules;
    survival_rules_ = survival_rules;
}

void GameOfLife::OfflineMode(int number_of_iterations) {
    for (int i = 0; i < number_of_iterations; i++) {
        Update();
    }
}

bool GameOfLife::LoadUniverse(std::vector<std::pair<int, int>> alive_cells) {
    field_.ResizeGrid(20, 20); // размер по умолчанию: 20x20

    // очищаем поле
    int rows = field_.GetRows();
    int cols = field_.GetCols();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (field_.GetCell(i, j)->IsAlive()) {
                field_.ToggleCellState(i, j);
            }
        }
    }

    // устанавливаем новое состояние для клеток
    for (const auto& cell : alive_cells) {
        int row = cell.first;
        int col = cell.second;
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            field_.ToggleCellState(row, col);
        }
        else {
            return false;
        }
    }

    return true;
}

int GameOfLife::CountAliveNeighbors(int row, int col) const {
    int count = 0;
    int rows = field_.GetRows();
    int cols = field_.GetCols();

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) { // пропускаем саму клетку
                continue;
            }

            int neighbor_row = (row + i + rows) % rows;
            int neighbor_col = (col + j + cols) % cols;

            if (field_.GetCell(neighbor_row, neighbor_col)->IsAlive()) {
                count++;
            }
        }
    }

    return count;
}

Field& GameOfLife::GetField() {
    return field_;
}

QString GameOfLife::GetRules() {
    QString birth_str;
    QString survival_str;

    for (int rule : birth_rules_) {
        birth_str += QString::number(rule);
    }

    for (int rule : survival_rules_) {
        survival_str += QString::number(rule);
    }

    return "B" + birth_str + "/S" + survival_str;
}
