#ifndef TASKONEDIALOG_H
#define TASKONEDIALOG_H

#include <QDialog>
#include <QMenuBar>
#include <QFileDialog>

class AboutAppDialog;

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
    void on_savePushButton_clicked();
    void on_openPushButton_clicked();
    void on_aboutPushButton_clicked();

    void reject() override;

private:
    void save();
    QString load();
    Ui::TaskOneDialog *ui;
    QWidget* w;
    std::unique_ptr<QMenuBar> menu;
    std::unique_ptr<QFileDialog> io_dialog;
    std::unique_ptr<AboutAppDialog> about_dialog;
};

#endif // TASKONEDIALOG_H
