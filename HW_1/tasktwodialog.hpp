#pragma once

#include <QDialog>

namespace Ui {
class TaskTwoDialog;
}

class TaskTwoDialog : public QDialog
{
    Q_OBJECT

private slots:
    void on_calcPushButton_clicked();
    void on_exitPushButton_clicked();

public:
    explicit TaskTwoDialog(QWidget *parent = nullptr);
    ~TaskTwoDialog();

private:
    Ui::TaskTwoDialog *ui;
    QWidget* w;
    float a, b, alpha;
};

