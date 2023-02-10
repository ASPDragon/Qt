#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TaskOneDialog;
class TaskTwoDialog;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<TaskOneDialog> taskOne;
    std::unique_ptr<TaskTwoDialog> taskTwo;
};
#endif // MAINWINDOW_H
