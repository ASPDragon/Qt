#ifndef PARSETEXT_H
#define PARSETEXT_H

#include <QString>
#include <QMap>

constexpr char* PATTERN_BEG = "#@";
constexpr char* PATTERN_END = "@";

class ParseText
{
public:
    ParseText() {};
    QString parse(QString&);

private:
    QMap<QString, QString> currencies_ = {{"EURO", "€"}, {"USD", "$"}};
};

#endif // PARSETEXT_H
