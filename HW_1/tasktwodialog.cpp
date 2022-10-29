#include "tasktwodialog.hpp"
#include "ui_tasktwodialog.h"
#include <QtMath>
#include <cmath>

TaskTwoDialog::TaskTwoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskTwoDialog)
{
    ui->setupUi(this);
    w = parent;
    ui->degreeRadioButton->setChecked(true);
}

void TaskTwoDialog::on_calcPushButton_clicked()
{
    float angle;
    bool aConversionSuccess;
    bool bConversionSuccess;
    bool alphaConversionSuccess;
    a = ui->aLineEdit->text().toFloat(&aConversionSuccess);
    b = ui->bLineEdit->text().toFloat(&bConversionSuccess);
    alpha = ui->alphaLineEdit->text().toFloat(&alphaConversionSuccess);

    if (!aConversionSuccess || !bConversionSuccess || !alphaConversionSuccess)
        ui->cLcdNumber->display("Error!");
    else {
        if (ui->radRadioButton->isChecked()) {
            angle = alpha;
        }
        else
            angle = qDegreesToRadians(ui->alphaLineEdit->text().toFloat());

        float result = qSqrt(qPow(a, 2) + qPow(b, 2) - 2 * a * b * qCos(angle));
        ui->cLcdNumber->display(result);
    }
}

void TaskTwoDialog::on_exitPushButton_clicked()
{
    this->close();
    w->show();
}

TaskTwoDialog::~TaskTwoDialog()
{
    delete ui;
}
