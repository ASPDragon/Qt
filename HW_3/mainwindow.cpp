#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskonedialog.h"
#include "tasktwodialog.h"

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

void MainWindow::on_buttonBox_accepted()
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
}


void MainWindow::on_buttonBox_rejected()
{
    this->close();
}

