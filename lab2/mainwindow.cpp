#include <QMessageBox>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(GameController &controller, View &view, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), controller_(controller), view_(view) {
    ui->setupUi(this); // настройка всех компонентов и виджетов, определённых в .ui файле

    ui->graphicsView->setScene(view.GetScene()); // устанавливаем сцену из view в виджет graphicsView

    setWindowTitle("Жизнь"); // утановка заголовка окна

    // подключаем сигналы кнопок к соответствующим слотам для обработки нажатий
    connect(ui->start_stop_button, &QPushButton::clicked, this, &MainWindow::OnStartStopClicked);
    connect(ui->resize_button, &QPushButton::clicked, this, &MainWindow::OnResizeClicked);
    connect(ui->apply_rules_button, &QPushButton::clicked, this, &MainWindow::OnApplyRulesButtonClicked);
    connect(ui->offline_mode_button, &QPushButton::clicked, this, &MainWindow::OnOfflineModeButtonClicked);
    connect(ui->load_universe_button, &QPushButton::clicked, this, &MainWindow::OnLoadUniverseButtonClicked);
    connect(ui->save_universe_button, &QPushButton::clicked, this, &MainWindow::OnSaveUniverseButtonClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::OnStartStopClicked() {
    if (controller_.IsRunning()) {
        controller_.Stop();
        ui->start_stop_button->setText("Начать игру");
    }
    else {
        controller_.Start();
        ui->start_stop_button->setText("Остановить игру");
    }
}

void MainWindow::OnResizeClicked() {
    StopGame();

    QString rows = ui->rows_input->text();
    QString cols = ui->cols_input->text();

    if (!controller_.Resize(rows, cols)) {
        QMessageBox::warning(this, "Неверный ввод", "Пожалуйста, введите положительные целые числа для строк и столбцов.");
        return;
    }
}

void MainWindow::OnApplyRulesButtonClicked() {
    StopGame();

    QString birth_rules = ui->birth_rules_input->text();
    QString survival_rules = ui->survival_rules_input->text();

    if (!controller_.ApplyRules(birth_rules, survival_rules)) {
        QMessageBox::warning(this, "Неверный ввод", "Пожалуйста, введите числа из множества {0...8}.");
        return;
    }
}

void MainWindow::OnOfflineModeButtonClicked() {
    StopGame();

    QString iterations = ui->offline_mode_input->text();

    if (!controller_.OfflineMode(iterations)) {
        QMessageBox::warning(this, "Неверный ввод", "Пожалуйста, введите положительное число.");
        return;
    }
}

void MainWindow::OnLoadUniverseButtonClicked() {
    StopGame();

    QString filename = QFileDialog::getOpenFileName(this, "Загрузить вселенную", "", "Life Files (*.life)");
    if (!filename.isEmpty()) {
        if (controller_.LoadUniverse(filename)) {
            QMessageBox::information(this, "Успех", "Вселенная успешно загружена!");
        }
        else {
            QMessageBox::critical(this, "Ошибка", "Не получилось загрузить вселенную.");
        }
    }
}

void MainWindow::OnSaveUniverseButtonClicked() {
    StopGame();

    QString filename = QFileDialog::getSaveFileName(this, "Сохранить вселенную", "", "Life Files (*.life)");
    if (filename.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Файл не выбран. Вселенная не была сохранена.");
        return;
    }

    if (controller_.SaveUniverse(filename)) {
        QMessageBox::information(this, "Успех", "Вселенная успешно сохранена!");
    }
    else {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить вселенную.");
    }
}

void MainWindow::StopGame() {
    if (controller_.IsRunning()) {
        controller_.Stop();
        ui->start_stop_button->setText("Начать игру");
    }
}
