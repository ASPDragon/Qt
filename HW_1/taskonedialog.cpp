#include "taskonedialog.hpp"
#include "ui_taskonedialog.h"
#include <QtMath>

TaskOneDialog::TaskOneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskOneDialog)
{
    ui->setupUi(this);
    w = parent;
}

void TaskOneDialog::on_calcPushButton_clicked()
{
    a = ui->aLineEdit->text().toInt();
    b = ui->bLineEdit->text().toInt();
    c = ui->cLineEdit->text().toInt();
    discriminant = qPow(b, 2) - 4 * a * c;

    if (discriminant > 0) {
        x1 = (-b + qSqrt(discriminant)) / (2 * a);
        x2 = (-b - qSqrt(discriminant)) / (2 * a);
        res1 = QString::number(x1);
        res2 = QString::number(x2);
    }
    else if (discriminant == 0) {
        x1 = -b / (2 * a);
        res1 = QString::number(x1);
        res2 = QString::number(x1);
    }
    else {
        res1 = QString("There is no root");
        res2 = res1;
    }

    ui->x1LineEdit->setText(res1);
    ui->x2LineEdit->setText(res2);
}

void TaskOneDialog::on_exitPushButton_clicked()
{
    this->close();
    w->show();
}

TaskOneDialog::~TaskOneDialog()
{
    delete ui;
}
