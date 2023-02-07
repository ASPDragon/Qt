#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "taskone.h"
#include "tasktwo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_nextPushButton_clicked()
{
    if (ui->taskOneRadioButton->isChecked()) {
        taskOne = std::make_unique<TaskOne>(this);
        taskOne->show();
        this->hide();
    }
    else if (ui->taskTwoRadioButton->isChecked()) {
        taskTwo = std::make_unique<TaskTwo>(this);
        taskTwo->show();
        this->hide();
    }
}


void MainWindow::on_exitPushButton_clicked()
{
    this->close();
}
