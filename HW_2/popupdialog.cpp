#include "popupdialog.h"
#include "ui_popupdialog.h"

PopUpDialog::PopUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopUpDialog)
{
    ui->setupUi(this);
}

PopUpDialog::~PopUpDialog()
{
    delete ui;
}

QString PopUpDialog::on_buttonBox_accepted()
{
    return ui->languageNameLineEdit->text();
}


void PopUpDialog::on_buttonBox_rejected()
{
    this->close();
}

