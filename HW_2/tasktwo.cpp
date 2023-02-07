#include "tasktwo.h"
#include "ui_tasktwo.h"
#include "popupdialog.h"
#include <QListWidgetItem>

TaskTwo::TaskTwo(QWidget *parent) :
    QDialog(parent), w(parent),
    ui(new Ui::TaskTwo)
{
    ui->setupUi(this);
    ui->programmingLanguageListWidget->setIconSize(QSize(48,48));
    ui->programmingLanguageListWidget->dragEnabled();
    ui->programmingLanguageListWidget->setDragDropMode(QAbstractItemView::InternalMove);

    foreach(const QString& item, LIST_ITEMS) {
        QListWidgetItem* listItem = new QListWidgetItem(item);
        listItem->setIcon(QPixmap(icon_path + item + ".png"));
        // Включаем возможность редактирования
        listItem->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
        ui->programmingLanguageListWidget->addItem(listItem);
    }
}

TaskTwo::~TaskTwo()
{
    delete ui;
}

void TaskTwo::on_addPushButton_clicked()
{
    auto popUp = std::make_unique<PopUpDialog>(this);
    popUp->exec();
    QString name = popUp->on_buttonBox_accepted();
    QListWidgetItem* listItem = new QListWidgetItem;
    listItem->setIcon(QPixmap(":/icons/unknown.png"));
    listItem->setText(name);
    // Включаем возможность редактирования
    listItem->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
    ui->programmingLanguageListWidget->addItem(listItem);
    popUp->close();
}


void TaskTwo::on_iconModeCheckBox_stateChanged(int arg1)
{
    if (ui->iconModeCheckBox->isChecked())
        ui->programmingLanguageListWidget->setViewMode(QListWidget::IconMode);
    else
        ui->programmingLanguageListWidget->setViewMode(QListWidget::ListMode);
}


void TaskTwo::on_deletePushButton_clicked()
{
    auto items = ui->programmingLanguageListWidget->selectedItems();

    foreach(auto item, items)
        delete ui->programmingLanguageListWidget->takeItem(ui->programmingLanguageListWidget->row(item));
}


void TaskTwo::on_exitPushButton_clicked()
{
    w->show();
    this->close();
}

