#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
//    translator.load(":/misc_files/translate/QtLanguage_ru.qm");
    MainWindow w;
    w.show();
    return a.exec();
}
