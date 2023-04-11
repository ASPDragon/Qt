#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTranslator>
#include <QActionGroup>

class Settings;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    void languageChange(QTranslator *);
    void setMap(QMap<QString, QKeySequence>&);

    QKeySequence newFile() const;
    QKeySequence openFile() const;
    QKeySequence readOnlyMode() const;
    QKeySequence saveFile() const;
    QKeySequence quit() const;

private slots:
    void on_newFilePushButton_clicked();
    void on_openPushButton_clicked();
    void on_savePushButton_clicked();
    void on_aboutPushButton_clicked();
    void on_readOnlyPushButton_clicked();
    void on_actionPreferences_triggered();

    void on_actionEnglish_triggered();
    void on_actionRussian_triggered();

    void exit();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void changeEvent(QEvent *) override;
    void createAction(const char *, QAction *, QIcon &&, QKeySequence, bool);

    Ui::MainWindow *ui;
    QSharedPointer<QMenu> menuFile;
    QSharedPointer<QTranslator> translator;
    QSharedPointer<QActionGroup> languageGrp;
    QString fileNm;
    QSharedPointer<Settings> settings;
    QMap<QString, QAction*> menuMap;
};
#endif // MAINWINDOW_H
