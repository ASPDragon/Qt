#include "aboutappdialog.h"
#include "ui_aboutappdialog.h"

#include <QFile>
#include <QMessageBox>

AboutAppDialog::AboutAppDialog(QWidget *parent) :
    QDialog(parent),
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

void AboutAppDialog::reject() {
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "About Programm", tr("Are you sure?\n"),
                                                                   QMessageBox::Cancel | QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        this->close();
    }
}
