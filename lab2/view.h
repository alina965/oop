#pragma once

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QEvent>
#include <QVector>
#include <vector>
#include "gameoflife.h"

class View : public QObject {
    Q_OBJECT
public:
    explicit View(GameOfLife &game, QGraphicsScene *scene, QObject *parent = nullptr);
    void Update();
    QGraphicsScene *GetScene();
    void DrawInitialField();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override; // метод, позволяющий перехватывать и обрабатывать события
private:
    GameOfLife &game_;
    QGraphicsScene *scene_;
    std::vector<QGraphicsRectItem*> cells_;
    const int cell_size_;
};
