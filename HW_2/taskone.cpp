#include "taskone.h"
#include "ui_taskone.h"
#include "parsetext.h"

#include <iterator>

TaskOne::TaskOne(QWidget *parent) :
    QDialog(parent), w(parent),
    ui(new Ui::TaskOne)
{
    ui->setupUi(this);
}

TaskOne::~TaskOne()
{
    delete ui;
}

void TaskOne::on_taskOneTextEdit_textChanged()
{
    qint32 pos = 0;
     text = ui->taskOneTextEdit->toPlainText();

    while (true) {
        qint32 fnd = text.indexOf(PATTERN_BEG, pos);

        if (fnd == -1) return;

        pos = fnd + 2;
        int r = text.indexOf(PATTERN_END, pos);

        if (r != -1) {
            ParseText parser;
            QString answer, substr;
            substr = text.mid(fnd + 2, r - (fnd + 2));
            answer = parser.parse(substr);
            text.replace(fnd + 2, substr.size(), answer);
            text.remove(fnd, 2);
            text.remove(pos - 1, 1);
            ui->taskOneTextEdit->setPlainText(text);
        }
    }
}

void TaskOne::on_exitPushButton_clicked()
{
    this->close();
    w->show();
}

