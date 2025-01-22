#include <QApplication>
#include "gameoflife.h"
#include "view.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GameOfLife game(20, 20);
    QGraphicsScene scene;
    View view(game, &scene, nullptr);
    GameController controller(game, view);
    MainWindow main_window(controller, view);
    main_window.show();
    return a.exec();
}
