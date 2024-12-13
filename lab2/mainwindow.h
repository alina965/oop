#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <memory>
#include "gamecontroller.h"
#include "view.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(GameController &controller, View &view, QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void OnStartStopClicked();
    void OnResizeClicked();
    void OnApplyRulesButtonClicked();
    void OnOfflineModeButtonClicked();
    void OnLoadUniverseButtonClicked();
    void OnSaveUniverseButtonClicked();
private:
    Ui::MainWindow *ui;
    GameController &controller_;
    View &view_;
    void StopGame();
};
