#include "filesystemdialog.hpp"
#include "ui_filesystemdialog.h"

#include <QFileSystemModel>

FileSystemDialog::FileSystemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileSystemDialog)
{
    ui->setupUi(this);
    auto model = new QFileSystemModel(this);
    model->setRootPath(QDir::rootPath());
    ui->treeView->setModel(model);

    connect(model, SIGNAL(directoryLoaded(const QString&)), ui->lineEdit, SLOT(setText(const QString&)));
}

FileSystemDialog::~FileSystemDialog()
{
    delete ui;
}
