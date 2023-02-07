#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TaskOne;
class TaskTwo;
//class TaskThree;

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
    std::unique_ptr<TaskOne> taskOne;
    std::unique_ptr<TaskTwo> taskTwo;
//    std::unique_ptr<TaskThree> taskThree;
};
#endif // MAINWINDOW_H
