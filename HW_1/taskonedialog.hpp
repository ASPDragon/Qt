#pragma once

#include <QDialog>

namespace Ui {
class TaskOneDialog;
}

class TaskOneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskOneDialog(QWidget *parent = nullptr);
    ~TaskOneDialog();

private slots:
    void on_calcPushButton_clicked();
    void on_exitPushButton_clicked();

private:
    Ui::TaskOneDialog *ui;
    QWidget *w;
    qint32 a, b, c, x1, x2, discriminant, realPart, imagionaryPart;
    QString res1, res2;
};

