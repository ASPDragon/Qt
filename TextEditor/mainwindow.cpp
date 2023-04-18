#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSharedPointer>
#include <QShortcut>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTextEdit>
#include <QScrollArea>
#include <QTabBar>
#include <QPrinter>
#include <QPrintDialog>>

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
    themeGrp = QSharedPointer<QActionGroup>::create(this);
    ui->actionEnglish->setCheckable(true);
    ui->actionRussian->setCheckable(true);
    ui->actionLight->setCheckable(true);
    ui->actionDark->setCheckable(true);

    ui->tabWidget->setTabPosition(QTabWidget::South);
    ui->tabWidget->setTabsClosable(true);
    ui->tabWidget->clear();

    languageGrp->addAction(ui->actionEnglish);
    languageGrp->addAction(ui->actionRussian);
    ui->actionEnglish->setChecked(true);

    themeGrp->addAction(ui->actionLight);
    themeGrp->addAction(ui->actionDark);
    ui->actionLight->setChecked(true);

    ui->currentLanguageLabel->setPixmap(QPixmap(":/misc_files/pictures/united-kingdom.png")
                                        .scaled(25, 50, Qt::KeepAspectRatio));

    ui->boldPushButton->setIcon(QPixmap(":/misc_files/pictures/bold.png"));
    ui->underlinePushButton->setIcon(QPixmap(":/misc_files/pictures/underlined-text.png"));

    menuMap.insert(ui->actionNew->text(), ui->actionNew);
    menuMap.insert(ui->actionOpen->text(), ui->actionOpen);
    menuMap.insert(ui->actionRead_Only->text(), ui->actionRead_Only);
    menuMap.insert(ui->actionSave->text(), ui->actionSave);
    menuMap.insert(ui->actionPrint->text(), ui->actionPrint);
    menuMap.insert(ui->actionQuit->text(), ui->actionQuit);

    for (auto action : menuMap.asKeyValueRange()) {
        auto it = settings->getMap().find(action.first);
        if (it != settings->getMap().end())
            action.second->setShortcut(it.value());
    }

    connect(ui->actionNew, SIGNAL(triggered(bool)), SLOT(on_newFilePushButton_clicked()));
    connect(ui->actionOpen, SIGNAL(triggered()), SLOT(on_openPushButton_clicked()));
    connect(ui->actionRead_Only, SIGNAL(triggered()), SLOT(on_readOnlyPushButton_clicked()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), SLOT(on_savePushButton_clicked()));
    connect(ui->actionQuit, SIGNAL(triggered(bool)), SLOT(closeEvent()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), SLOT(on_aboutPushButton_clicked()));
    connect(ui->actionPreferences, SIGNAL(clicked()), SLOT(on_actionPreferences_triggered()));
    connect(ui->actionDark, SIGNAL(clicked()), SLOT(on_actionDarkTheme_triggered()));
    connect(ui->actionLight, SIGNAL(clicked()), SLOT(on_actionLightTheme_triggered()));

    on_newFilePushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newFilePushButton_clicked()
{
    QPair<QScrollArea*, QTextEdit*> page = newDoc(false);
    ui->tabWidget->addTab(page.first, "Tab #" + QString::number(ui->tabWidget->currentIndex()));
}

void MainWindow::on_openPushButton_clicked()
{
    fileNm.clear();
    fileNm = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                        "All files(*.*);;Text File (*.txt);;Document Office Open XML (*.docx);;Text OpenDocument (*.odt)");

    QFile file(fileNm);
    QPair<QScrollArea*, QTextEdit*> page = newDoc(false);
    ui->tabWidget->addTab(page.first, QString::fromStdString(file.filesystemFileName().filename().string()));
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray byte_array = file.readAll();
        page.second->setPlainText(byte_array);
        tabs.insert(ui->tabWidget->currentIndex(), ui->tabWidget->tabBar());
    }
}

void MainWindow::on_readOnlyPushButton_clicked() {
    on_openPushButton_clicked();
    auto doc = tabsContent.find(ui->tabWidget->currentIndex());
    if (doc != tabsContent.end())
        doc.value()->setReadOnly(true);
}

void MainWindow::on_savePushButton_clicked()
{
    QString currentTabName = ui->tabWidget->tabBar()->tabText(ui->tabWidget->currentIndex());

    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), currentTabName,
                                                        "All files(*.*);;Text File (*.txt);;Document Office Open XML (*.docx);;Text OpenDocument (*.odt)");
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        auto doc = tabsContent.find(ui->tabWidget->currentIndex());
        if (currentTabName.isEmpty()) {
            ui->tabWidget->tabBar()->setTabText(ui->tabWidget->currentIndex(), QString::fromStdString(file.filesystemFileName().filename().string()));
        }
        if (doc != tabsContent.end()) {
            QByteArray byte_array = doc.value()->toPlainText().toUtf8();
            file.write(byte_array, byte_array.length());
        }
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
    connect(preferences, &PreferencesDialog::mapUpdate, [&](const QMap<QString, QKeySequence>& seqMap) {
        for (auto sequence : seqMap.asKeyValueRange()) {
            auto it = menuMap.find(sequence.first);

            if (it != menuMap.end())
                it.value()->setShortcut(sequence.second);
        }
    });
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

QPair<QScrollArea*, QTextEdit*> MainWindow::newDoc(bool flag) {
    auto scrollArea = new QScrollArea(this);
    auto textEdit = new QTextEdit(this);
    textEdit->setReadOnly(flag);
    textEdit->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(textEdit);

    return qMakePair(scrollArea, textEdit);
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


void MainWindow::on_actionDark_triggered()
{
    this->setStyleSheet("QMainWindow { background-color:dimgrey; }"
                        "QPushButton { background-color:darkgrey; }"
                        "QTextEdit { background-color:#d7d6d5; }"
                        "QMenu { background-color:dimgrey; }"
                        "QAction { background-color: dimgrey; }");
}


void MainWindow::on_actionLight_triggered()
{
    this->setStyleSheet("");
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    auto printDialog = new QPrintDialog(&printer, this);
    printDialog->setWindowTitle(tr("Print Document"));

    if (printDialog->exec() != QDialog::Accepted)
        return;

    auto tab = tabsContent.find(ui->tabWidget->currentIndex());

    if (tab != tabsContent.end())
        tab.value()->document()->print(&printer);
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

