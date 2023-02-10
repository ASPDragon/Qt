#ifndef TASKTWO_H
#define TASKTWO_H

#include <QDialog>
#include <QStandardItemModel>
#include <QListView>

class PopUpDialog;

namespace Ui {
class TaskTwo;
}

static const QStringList LIST_ITEMS =
    QStringList() << "cplusplus" << "csharp" << "Java" << "javascript" << "PHP" << "Python";

class TaskTwo : public QDialog
{
    Q_OBJECT

public:
    explicit TaskTwo(QWidget *parent = nullptr);
    ~TaskTwo();

private slots:
    void on_addPushButton_clicked();

    void on_iconModeCheckBox_stateChanged(int arg1);

    void on_deletePushButton_clicked();

    void on_exitPushButton_clicked();

private:
    Ui::TaskTwo *ui;
    QWidget* w;
    std::unique_ptr<QStandardItemModel> model;
    QString icon_path = ":/icons/";
};

#endif // TASKTWO_H
