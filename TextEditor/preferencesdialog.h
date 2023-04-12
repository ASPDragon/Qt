#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>

class Settings;
class QComboBox;

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QSharedPointer<Settings>&& settings, QWidget* parent = nullptr);
    ~PreferencesDialog();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

signals:
    void mapUpdate(const QMap<QString, QKeySequence>&);

private:
    Ui::PreferencesDialog *ui;
    QList<QKeySequence> listOfSequences;
    QSharedPointer<Settings> settings;
    QMap<QString, QComboBox*> comboBoxMap;
    QWidget *w;
};

#endif // PREFERENCESDIALOG_H
