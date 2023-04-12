#ifndef ABOUTAPPDIALOG_H
#define ABOUTAPPDIALOG_H

#include <QDialog>

namespace Ui {
class AboutAppDialog;
}

class AboutAppDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutAppDialog(QWidget *parent = nullptr);
    ~AboutAppDialog();

private slots:
    void reject() override;

private:
    Ui::AboutAppDialog *ui;
    QWidget* w;
};

#endif // ABOUTAPPDIALOG_H