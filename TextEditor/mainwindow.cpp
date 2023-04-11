#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSharedPointer>
#include <QShortcut>
#include <QMessageBox>
#include <QCloseEvent>

#include "aboutappdialog.h"
#include "preferencesdialog.h"
#include "settings.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Text Editor"));
    settings = QSharedPointer<Settings>::create();
    translator = QSharedPointer<QTranslator>::create();

    languageGrp = QSharedPointer<QActionGroup>::create(this);
    ui->actionEnglish->setCheckable(true);
    ui->actionRussian->setCheckable(true);

    languageGrp->addAction(ui->actionEnglish);
    languageGrp->addAction(ui->actionRussian);
    ui->actionEnglish->setChecked(true);
    ui->currentLanguageLabel->setPixmap(QPixmap(":/misc_files/pictures/united-kingdom.png")
                                        .scaled(25, 50, Qt::KeepAspectRatio));

    menuMap.insert(ui->actionNew->text(), ui->actionNew);
    menuMap.insert(ui->actionOpen->text(), ui->actionOpen);
    menuMap.insert(ui->actionRead_Only->text(), ui->actionRead_Only);
    menuMap.insert(ui->actionSave->text(), ui->actionSave);
    menuMap.insert(ui->actionQuit->text(), ui->actionQuit);

    for (auto action : menuMap.asKeyValueRange()) {
        auto it = settings->getMap().find(action.first);
        if (it != settings->getMap().end())
            action.second->setShortcut(it.value());
    }

    connect(ui->actionNew, SIGNAL(triggered(bool)), SLOT(on_newFilePushButton_clicked()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), SLOT(on_openPushButton_clicked()));
    connect(ui->actionRead_Only, SIGNAL(triggered(bool)), SLOT(on_readOnlyPushButton_clicked()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), SLOT(on_savePushButton_clicked()));
    connect(ui->actionQuit, SIGNAL(triggered(bool)), SLOT(closeEvent()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), SLOT(on_aboutPushButton_clicked()));
    connect(ui->actionPreferences, SIGNAL(clicked()), SLOT(on_actionPreferences_triggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newFilePushButton_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::on_openPushButton_clicked()
{
    ui->textEdit->clear();
    fileNm.clear();
    ui->textEdit->setReadOnly(false);

    fileNm = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                        "All files(*.*);;Text File (*.txt);;Document Office Open XML (*.docx);;Text OpenDocument (*.odt)");
    QFile file(fileNm);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray byte_array = file.readAll();
        ui->textEdit->setPlainText(byte_array);
    }
}

void MainWindow::on_readOnlyPushButton_clicked() {
    on_openPushButton_clicked();
    ui->textEdit->setReadOnly(true);
}

void MainWindow::on_savePushButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), fileNm,
                                                        "All files(*.*);;Text File (*.txt);;Document Office Open XML (*.docx);;Text OpenDocument (*.odt)");
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QByteArray byte_array = ui->textEdit->toPlainText().toUtf8();
        file.write(byte_array, byte_array.length());
    }
}


void MainWindow::on_aboutPushButton_clicked()
{
    auto about_dialog = QSharedPointer<AboutAppDialog>::create(this);
    about_dialog->exec();
}

void MainWindow::on_actionPreferences_triggered()
{
    auto preferences = new PreferencesDialog(std::move(settings), this);
    connect(preferences, SIGNAL(mapUpdate()), this, SLOT([&](const QMap<QString, QKeySequence>& seqMap) {
        for (auto sequence : seqMap.asKeyValueRange()) {
            auto it = menuMap.find(sequence.first);

            if (it != menuMap.end())
                it.value()->setShortcut(sequence.second);
        }
    }));
    preferences->exec();
}

void MainWindow::on_actionEnglish_triggered()
{
    ui->currentLanguageLabel->setPixmap(QPixmap(":/misc_files/pictures/united-kingdom.png").scaled(25, 50, Qt::KeepAspectRatio));
    QApplication::removeTranslator(translator.data());
    ui->retranslateUi(this);
}

void MainWindow::on_actionRussian_triggered()
{
    if (translator->load(":/misc_files/translate/QtLanguage_ru.qm")) {
        ui->currentLanguageLabel->setPixmap(QPixmap(":/misc_files/pictures/russia.png").scaled(25, 50, Qt::KeepAspectRatio));
        QApplication::installTranslator(translator.data());
        ui->retranslateUi(this);
    }
}

void MainWindow::exit() {}

void MainWindow::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {}
}

void MainWindow::createAction(const char *name, QAction *action, QIcon &&icon, QKeySequence button, bool isCheckable) {
    action->setText(tr(name));
    action->setIcon(icon);
    action->setShortcut(button);
    action->setCheckable(isCheckable);
}

void MainWindow::setMap(QMap<QString, QKeySequence>& someMap) {
    for (auto sequence : someMap.asKeyValueRange()) {
        auto it = menuMap.find(sequence.first);

        if (it != menuMap.end())
            it.value()->setShortcut(sequence.second);
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton result = QMessageBox::question(
                this, tr("Text_Editor"), tr("Are you sure?\n"), QMessageBox::Cancel | QMessageBox::Yes);

    if (result != QMessageBox::Yes)
        event->ignore();
    else
        event->accept();
}

