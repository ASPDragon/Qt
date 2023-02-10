#include "tasktwodialog.h"
#include "ui_tasktwodialog.h"
#include <QFile>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>

#include "aboutappdialog.h"

TaskTwoDialog::TaskTwoDialog(QWidget *parent) :
    QDialog(parent), w(parent),
    ui(new Ui::TaskTwoDialog)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

TaskTwoDialog::~TaskTwoDialog()
{
    delete ui;
}

void TaskTwoDialog::clear() {
    ui->weatherLineEdit->clear();
    ui->usdLineEdit->clear();
    ui->euroLineEdit->clear();
}

void TaskTwoDialog::on_openPushButton_clicked()
{
    ui->textEdit->clear();
    this->clear();
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", "All files(*.*);;HTML File (*.html)");
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray byte_array = file.readAll();
        ui->textEdit->setPlainText(byte_array);
    }
}


void TaskTwoDialog::on_aboutPushButton_clicked()
{
    about_dialog = std::make_unique<AboutAppDialog>(this);
    about_dialog->exec();
}

void TaskTwoDialog::reject() {
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Task One", tr("Are you sure?\n"),
                                                               QMessageBox::Cancel | QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        this->close();
        w->show();
    }
}

void TaskTwoDialog::on_showInfoPushButton_clicked()
{
    this->clear();
    QStringList list = this->getData();
    ui->weatherLineEdit->setText(list[0]);
    ui->usdLineEdit->setText(list[1]);
    ui->euroLineEdit->setText(list[2]);
}

QStringList TaskTwoDialog::getData() {
    QStringList list;
    QRegularExpression weather_expr{R"regex(weather-temp">(-?\d+))regex"};
    QRegularExpression currencies_expr{R"regex(<a href="https://news.mail.ru/currency/src/MOEX/charcode/(\w+)/.*?<div class="rate__currency eff-hccl__1qf1sov">(\d+,\d+)</div>)regex"};

    weather_expr.setPatternOptions(QRegularExpression::DotMatchesEverythingOption);
    auto wres = weather_expr.globalMatch(ui->textEdit->toPlainText());
    for (const QRegularExpressionMatch &match : wres)
        list.append(match.captured(1));

    currencies_expr.setPatternOptions(QRegularExpression::DotMatchesEverythingOption);
    auto res = currencies_expr.globalMatch(ui->textEdit->toPlainText());
    for (const QRegularExpressionMatch &match : res)
        list.append(match.captured(2));

    return list;
}
