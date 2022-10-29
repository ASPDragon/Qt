#include "taskthreedialog.hpp"
#include "ui_taskthreedialog.h"
#include <QDebug>

TaskThreeDialog::TaskThreeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskThreeDialog)
{
    ui->setupUi(this);
    w = parent;
}

TaskThreeDialog::~TaskThreeDialog()
{
    delete ui;
}

void TaskThreeDialog::on_replacerPushButton_clicked()
{
    ui->bTextEdit->setText(ui->aTextEdit->toPlainText());
}

void TaskThreeDialog::on_appendPushButton_clicked()
{
    ui->bTextEdit->append(ui->aTextEdit->toPlainText());
}

void TaskThreeDialog::on_htmlPushButton_clicked()
{
    ui->aTextEdit->setHtml("<font color='red'>Hello</font>");
}

void TaskThreeDialog::on_exitPushButton_clicked()
{
    this->close();
    w->show();
}
