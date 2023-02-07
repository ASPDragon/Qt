#ifndef TASKONE_H
#define TASKONE_H

#include <QDialog>
#include <QString>

namespace Ui {
class TaskOne;
}

class TaskOne : public QDialog
{
    Q_OBJECT

public:
    explicit TaskOne(QWidget *parent = nullptr);
    ~TaskOne();

private slots:
    void on_taskOneTextEdit_textChanged();

    void on_exitPushButton_clicked();

private:
    std::pair<size_t, size_t> find_next_pattern(std::string_view s, size_t search_start);
    Ui::TaskOne *ui;
    QString text;
    QWidget* w;
};

#endif // TASKONE_H
