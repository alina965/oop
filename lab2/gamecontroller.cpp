#include <unordered_set>
#include <QFile>
#include <regex>
#include "gamecontroller.h"

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

    for (QChar c : new_birth_rules) {
        int num = c.digitValue();
        if (num >= 0 && num <= 8) {
            birth_rules.insert(c.digitValue());
        }
        else {
            return false;
        }
    }

    for (QChar c : new_survival_rules) {
        int num = c.digitValue();
        if (num >= 0 && num <= 8) {
            survival_rules.insert(c.digitValue());
        }
        else {
            return false;
        }
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
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);

    if (in.readLine() != "Life 1.06") {
        return false;
    }

    QString name;
    QString line = in.readLine();
    if (line.startsWith("#N ")) {
        name = line.mid(3).trimmed();
    }
    else {
        return false;
    }

    QString new_rules;
    line = in.readLine();
    if (line.startsWith("#R ")) {
        QString rules = line.mid(3).trimmed();
        std::regex rule_regex(R"(^B[0-8]+/S[0-8]+$)");
        if (std::regex_match(rules.toStdString(), rule_regex)) {
            new_rules = rules;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }

    std::vector<std::pair<int, int>> alive_cells;
    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList coords = line.split(" ", Qt::SkipEmptyParts);
        if (coords.size() == 2) {
            int x = coords[0].toInt();
            int y = coords[1].toInt();
            alive_cells.emplace_back(x, y);
        }
        else {
            return false;
        }
    }

    std::unordered_set<int> birth_rules;
    std::unordered_set<int> survival_rules;

    int b_index = new_rules.indexOf('B');
    int s_index = new_rules.indexOf('S');

    QString birth_part = new_rules.mid(b_index + 1, s_index - b_index - 1);
    QString survival_part = new_rules.mid(s_index + 1);

    for (QChar c : birth_part) {
        birth_rules.insert(c.digitValue());
    }

    for (QChar c : survival_part) {
        survival_rules.insert(c.digitValue());
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
        return false;
    }

    return true;
}

bool GameController::IsRunning() const {
    return running_;
}
