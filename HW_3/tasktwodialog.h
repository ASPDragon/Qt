#ifndef TASKTWODIALOG_H
#define TASKTWODIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QStringList>

class AboutAppDialog;

namespace Ui {
class TaskTwoDialog;
}

class TaskTwoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskTwoDialog(QWidget *parent = nullptr);
    ~TaskTwoDialog();
    QStringList getData();

private slots:
    void on_openPushButton_clicked();
    void on_aboutPushButton_clicked();

    void reject() override;

    void on_showInfoPushButton_clicked();

private:
    void clear();
    Ui::TaskTwoDialog *ui;
    QWidget* w;
    std::unique_ptr<AboutAppDialog> about_dialog;
};

#endif // TASKTWODIALOG_H
