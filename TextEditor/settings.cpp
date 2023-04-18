#include "settings.hpp"
#include <QFile>
#include <QKeySequence>

Settings::Settings()
{
    QFile file("settings.ini");
    file.open(QIODeviceBase::ReadWrite);
    const QByteArray arr = file.readAll();

    if (!arr.isEmpty()) {
        QStringList lst = QString(arr).split('\n');
        lst.removeAll({});
        foreach (auto str, lst) {
            int pos = str.indexOf('-');
            map.insert(str.mid(0, pos),
                       QKeySequence::fromString(str.mid(pos + 1, str.length() - 1)));
        }
    }
    else {
        map.insert("New File", QKeySequence::New);
        map.insert("Open", QKeySequence::Open);
        map.insert("Read Only", QKeySequence(Qt::CTRL | Qt::Key_R));
        map.insert("Save", QKeySequence::Save);
        map.insert("Print", QKeySequence::Print);
        map.insert("Quit", QKeySequence(Qt::CTRL | Qt::Key_Q));
    }
}

void Settings::write() {
    QFile file("settings.ini");
    QTextStream stream(&file);

    if (file.open(QIODevice::WriteOnly)) {
        for (auto [key, value] : map.asKeyValueRange()) {
            stream << QString(key + '-' + value.toString() + '\n');
        }
    }
}

QMap<QString, QKeySequence>& Settings::getMap() {
    return map;
}
