#include <unordered_set>
#include <QFile>
#include <regex>
#include <exception>
#include <iostream>
#include "gamecontroller.h"
#include "filepopulator.h"
#include "randompopulator.h"

GameController::GameController(GameOfLife &game, View &view, QObject *parent) : QObject(parent), game_(game), view_(view), running_(false) {
    connect(&timer_, &QTimer::timeout, this, &GameController::UpdateGame); // связываем сигнал таймера timeout со слотом UpdateGame.
}

void GameController::Start() {
    if (!running_) {
        timer_.start(500); // таймер запускается с интервалом 500 миллисекунд
        running_ = true;
    }
}

void GameController::Stop() {
    if (running_) {
        timer_.stop();
        running_ = false;
    }
}

void GameController::UpdateGame() {
    game_.Update();
    view_.Update();
}

bool GameController::Resize(QString new_rows, QString new_cols) {
    bool ok1, ok2;
    int rows = new_rows.toInt(&ok1);
    int cols = new_cols.toInt(&ok2);

    if (!ok1 || !ok2 || rows <= 0 || cols <= 0) {
        return false;
    }

    game_.GetField().ResizeGrid(rows, cols);
    view_.DrawInitialField();
    return true;
}

bool GameController::ApplyRules(QString new_birth_rules, QString new_survival_rules) {
    std::unordered_set<int> birth_rules;
    std::unordered_set<int> survival_rules;

    if (!SetRules(birth_rules, new_birth_rules)) {
        return false;
    }

    if (!SetRules(survival_rules, new_survival_rules)) {
        return false;
    }

    game_.SetRules(birth_rules, survival_rules);

    return true;
}

bool GameController::OfflineMode(QString iterations) {
    bool ok;
    int int_iterations = iterations.toInt(&ok);

    if (!ok || int_iterations <= 0) {
        return false;
    }

    game_.OfflineMode(int_iterations);
    view_.DrawInitialField();

    return true;
}

bool GameController::LoadUniverse(QString filename) {
    FilePopulator populator(filename);

    std::vector<std::pair<int, int>> alive_cells;
    std::unordered_set<int> birth_rules;
    std::unordered_set<int> survival_rules;

    if (!populator.Populate(alive_cells, birth_rules, survival_rules)) {
        return false;
    }

    game_.SetRules(birth_rules, survival_rules);

    if (!game_.LoadUniverse(alive_cells)) {
        return false;
    }

    view_.DrawInitialField();

    return true;
}

bool GameController::SaveUniverse(QString filename) {
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);

    try {
        out << "Life 1.06\n";
        out << "#N " << "Universe" << "\n";

        QString rules = game_.GetRules();
        if (!rules.isEmpty()) {
            out << "#R " << rules << "\n";
        }
        else {
            return false;
        }

        int rows = game_.GetField().GetRows();
        int cols = game_.GetField().GetCols();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (game_.GetField().GetCell(i, j)->IsAlive()) {
                    out << i << " " << j << "\n";
                }
            }
        }
    }

    catch (...) {
        std::cout << "An error has occurred." << std::endl;
        return false;
    }

    return true;
}

bool GameController::IsRunning() const {
    return running_;
}

bool GameController::Random() {
    RandomPopulator populator;

    std::vector<std::pair<int, int>> alive_cells;
    std::unordered_set<int> birth_rules;
    std::unordered_set<int> survival_rules;

    populator.Populate(alive_cells, birth_rules, survival_rules);

    game_.SetRules(birth_rules, survival_rules);

    if (!game_.LoadUniverse(alive_cells)) {
        return false;
    }

    view_.DrawInitialField();

    return true;
}

bool GameController::SetRules(std::unordered_set<int>& rules, QString& new_rules) {
    for (QChar c : new_rules) {
        int num = c.digitValue();
        if (num >= 0 && num <= 8) {
            rules.insert(c.digitValue());
        }
        else {
            return false;
        }
    }

    return true;
}
