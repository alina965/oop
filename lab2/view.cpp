#include "view.h"
#include <QGraphicsSceneMouseEvent>

View::View(GameOfLife &game, QGraphicsScene *scene, QObject *parent) : QObject(parent), game_(game), scene_(scene), cell_size_(20) {
    DrawInitialField();
    scene_->installEventFilter(this);
}

void View::DrawInitialField() {
    scene_->clear();
    cells_.clear();

    int rows = game_.GetField().GetRows();
    int cols = game_.GetField().GetCols();

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            QRect cell_rect(col * cell_size_, row * cell_size_, cell_size_, cell_size_);
            bool is_alive = game_.GetField().GetCell(row, col)->IsAlive();
            auto *cell_item = scene_->addRect(cell_rect, QPen(Qt::gray), QBrush(is_alive ? Qt::black : Qt::white));
            cells_.push_back(cell_item);
        }
    }
}

bool View::eventFilter(QObject *watched, QEvent *event) {
    if (watched == scene_ && event->type() == QEvent::GraphicsSceneMousePress) {
        auto *mouse_event = static_cast<QGraphicsSceneMouseEvent*>(event);
        QPointF click_pos = mouse_event->scenePos();

        if (!scene_->sceneRect().contains(click_pos)) {
            return false;
        }

        int col = static_cast<int>(click_pos.x() / cell_size_);
        int row = static_cast<int>(click_pos.y() / cell_size_);

        int rows = game_.GetField().GetRows();
        int cols = game_.GetField().GetCols();

        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            game_.GetField().ToggleCellState(row, col);
            Update();
            return true;
        }
    }

    return QObject::eventFilter(watched, event);
}

void View::Update() {
    int rows = game_.GetField().GetRows();
    int cols = game_.GetField().GetCols();

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int index = row * cols + col;
            auto *cell_item = cells_[index];
            cell_item->setBrush(game_.GetField().GetCell(row, col)->IsAlive() ? Qt::black : Qt::white);
        }
    }
}

QGraphicsScene *View::GetScene() {
    return scene_;
}
