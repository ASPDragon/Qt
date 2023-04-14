#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

#include <QSettings>
#include <QComboBox>

#include "settings.hpp"

PreferencesDialog::PreferencesDialog(QSharedPointer<Settings>&& settings, QWidget* parent) :
    settings{settings}, QDialog{parent}, w{parent},
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);
    QStringList lstNew { "Ctrl+N", "Ctrl+T", "Ctrl+F" };
    QStringList lstOpen { "Ctrl+O", "Alt+Enter", "F5" };
    QStringList lstReadOnly { "Ctrl+R", "Ctrl+Minus" };
    QStringList lstSave { "Ctrl+S", "Ctrl+Plus" };
    QStringList lstQuit { "Ctrl+Q", "Ctrl+F4" };

    ui->newFileComboBox->addItems(lstNew);
    comboBoxMap.insert("New File", ui->newFileComboBox);
    ui->openFileComboBox->addItems(lstOpen);
    comboBoxMap.insert("Open File", ui->openFileComboBox);
    ui->saveFileComboBox->addItems(lstReadOnly);
    comboBoxMap.insert("Save", ui->saveFileComboBox);
    ui->readOnlyComboBox->addItems(lstSave);
    comboBoxMap.insert("Read Only", ui->readOnlyComboBox);
    ui->quitComboBox->addItems(lstQuit);
    comboBoxMap.insert("Quit", ui->quitComboBox);
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::on_buttonBox_accepted()
{
    for (auto comboBox : comboBoxMap.asKeyValueRange()) {
        auto key = settings.data()->getMap().find(comboBox.first);
        if (key != settings.data()->getMap().end())
            *key = QKeySequence::fromString(comboBox.second->currentText());
        else
            qDebug() << "Error!";
    }
    settings->write();
    emit mapUpdate(settings.data()->getMap());
    this->close();
}


void PreferencesDialog::on_buttonBox_rejected()
{
    this->close();
}
