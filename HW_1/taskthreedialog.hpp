#pragma once

#include <QDialog>

namespace Ui {
class TaskThreeDialog;
}

class TaskThreeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskThreeDialog(QWidget *parent = nullptr);
    ~TaskThreeDialog();

private slots:
    void on_appendPushButton_clicked();

    void on_replacerPushButton_clicked();

    void on_htmlPushButton_clicked();

    void on_exitPushButton_clicked();

private:
    Ui::TaskThreeDialog *ui;
    QWidget *w;
};

