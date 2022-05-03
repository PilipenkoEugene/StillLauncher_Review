#include "moduleadm.h"
#include "ui_moduleadm.h"
#include <QTableWidgetItem>

moduleAdm::moduleAdm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::moduleAdm)
{
    ui->setupUi(this);

}

moduleAdm::~moduleAdm()
{
    delete ui;
}

//В РАЗРАБОТКЕ.
//Модуль администрирования, будет использоваться пользователями с правами администратора
//для управления созданными записями и предоставленными доступами.
void moduleAdm::run(int id, QString log, QString pass, QString roleD)
{
    QTableWidgetItem *item;
    item = new QTableWidgetItem;

    item->setText(QString::number(id));
    ui->tableWidget->setItem(id - 1, 0, item);
    item->setText(log);
    ui->tableWidget->setItem(id - 1, 1, item);
    item->setText(pass);
    ui->tableWidget->setItem(id - 1, 2, item);
    item->setText(roleD);
    ui->tableWidget->setItem(id - 1, 3, item); //check
}
//___________________________________________________________________________________________//
