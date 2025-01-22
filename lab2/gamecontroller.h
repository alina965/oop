#pragma once

#include <QObject>
#include <QTimer>
#include <QString>
#include "gameoflife.h"
#include "view.h"

class GameController : public QObject {
    Q_OBJECT
public:
    explicit GameController(GameOfLife &game, View &view, QObject *parent = nullptr);
    void Start();
    void Stop();
    bool Resize(QString new_rows, QString new_cols);
    bool ApplyRules(QString new_birth_rules, QString new_survival_rules);
    bool OfflineMode(QString iterations);
    bool LoadUniverse(QString filename);
    bool SaveUniverse(QString filename);
    bool IsRunning() const;
    bool Random();
    bool SetRules(std::unordered_set<int>& rules, QString& new_rules);
private slots:
    void UpdateGame();
private:
    GameOfLife &game_;
    View &view_;
    QTimer timer_;
    bool running_;
};
