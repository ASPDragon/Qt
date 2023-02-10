#include "aboutappdialog.h"
#include "ui_aboutappdialog.h"
#include <QFile>

AboutAppDialog::AboutAppDialog(QWidget *parent) :
    QDialog(parent), w(parent),
    ui(new Ui::AboutAppDialog)
{
    ui->setupUi(this);
    ui->aboutTextEdit->setReadOnly(true);
    QFile file(":/misc_files/txt/about.txt");

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray byte_array = file.readAll();
        ui->aboutTextEdit->setPlainText(byte_array);
    }
}

AboutAppDialog::~AboutAppDialog()
{
    delete ui;
}

void AboutAppDialog::on_closePushButton_clicked()
{
    this->close();
}

