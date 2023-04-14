#pragma once

#include <QDialog>

namespace Ui {
class FileSystemDialog;
}

class FileSystemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileSystemDialog(QWidget *parent = nullptr);
    ~FileSystemDialog();

private:
    Ui::FileSystemDialog *ui;
};

