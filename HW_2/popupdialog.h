#ifndef POPUPDIALOG_H
#define POPUPDIALOG_H

#include <QDialog>

namespace Ui {
class PopUpDialog;
}

class PopUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PopUpDialog(QWidget *parent = nullptr);
    ~PopUpDialog();

public slots:
    QString on_buttonBox_accepted();

private slots:
    void on_buttonBox_rejected();

private:
    Ui::PopUpDialog *ui;
};

#endif // POPUPDIALOG_H
