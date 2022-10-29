#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "taskonedialog.hpp"
#include "tasktwodialog.hpp"
#include "taskthreedialog.hpp"

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
        taskOne = std::make_unique<TaskOneDialog>(this);
        taskOne->show();
        this->hide();
    }
    else if (ui->taskTwoRadioButton->isChecked()) {
        taskTwo = std::make_unique<TaskTwoDialog>(this);
        taskTwo->show();
        this->hide();
    }
    else if (ui->taskThreeRadioButton->isChecked()) {
        taskThree = std::make_unique<TaskThreeDialog>(this);
        taskThree->show();
        this->hide();
    }
}

void MainWindow::on_exitPushButton_clicked()
{
    this->close();
}

