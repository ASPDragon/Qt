#pragma once

#include <QMainWindow>

class TaskOneDialog;
class TaskTwoDialog;
class TaskThreeDialog;

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
    void on_nextPushButton_clicked();

    void on_exitPushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<TaskOneDialog> taskOne;
    std::unique_ptr<TaskTwoDialog> taskTwo;
    std::unique_ptr<TaskThreeDialog> taskThree;
};
