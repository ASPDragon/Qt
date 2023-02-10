#include "parsetext.h"
#include <QKeyValueIterator>

QString ParseText::parse(QString& str) {
    return currencies_.value(str, "");
}
