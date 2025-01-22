#include "filepopulator.h"
#include <QFile>
#include <QTextStream>
#include <regex>

FilePopulator::FilePopulator(const QString& filename) : filename_(filename) {}

bool FilePopulator::Populate(std::vector<std::pair<int, int>>& alive_cells,
              std::unordered_set<int>& birth_rules,
              std::unordered_set<int>& survival_rules) {
    QFile file(filename_);

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

    return true;
}
