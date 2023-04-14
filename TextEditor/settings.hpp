#pragma once

#include <QObject>
#include <QDir>

class Settings
{
public:
    Settings();
    void write();
    QMap<QString, QKeySequence>& getMap();

private:
    QMap<QString, QKeySequence> map;
};

