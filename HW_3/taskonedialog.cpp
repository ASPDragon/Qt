#include "taskonedialog.h"
#include "ui_taskonedialog.h"
#include <QLayout>
#include <QFile>
#include <QMessageBox>

#include "aboutappdialog.h"

TaskOneDialog::TaskOneDialog(QWidget *parent) :
    QDialog(parent), w(parent),
    ui(new Ui::TaskOneDialog)
{
    ui->setupUi(this);
//    this->setWindowState(Qt::WindowFullScreen);
//    menu = std::make_unique<QMenuBar>(this);
//    this->layout()->setMenuBar(menu.get());
//    this->layout()->menuBar()->addAction("Save");
}

TaskOneDialog::~TaskOneDialog()
{
    delete ui;
}

void TaskOneDialog::on_savePushButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                    "All files(*.*);;Text File (*.txt);;Document Office Open XML (*.docx);;Text OpenDocument (*.odt)");
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QByteArray byte_array = ui->textEdit->toPlainText().toUtf8();
        file.write(byte_array, byte_array.length());
    }
}


void TaskOneDialog::on_openPushButton_clicked()
{
    ui->textEdit->clear();
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                    "All files(*.*);;Text File (*.txt);;Document Office Open XML (*.docx);;Text OpenDocument (*.odt)");
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray byte_array = file.readAll();
        ui->textEdit->setPlainText(byte_array);
    }
}


void TaskOneDialog::on_aboutPushButton_clicked()
{
    about_dialog = std::make_unique<AboutAppDialog>(this);
    about_dialog->exec();
}

void TaskOneDialog::reject() {
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Task One", tr("Are you sure?\n"),
                                                               QMessageBox::Cancel | QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        this->close();
        w->show();
    }
}
