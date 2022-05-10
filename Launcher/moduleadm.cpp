#include "moduleadm.h"
#include "ui_moduleadm.h"

moduleAdm::moduleAdm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::moduleAdm)
{
    ui->setupUi(this);

    loginData.setDatabaseName("D:/stuff/Projects/sqlite/testdb.db");
    loginData.open();
    updateTable();
}

moduleAdm::~moduleAdm()
{
    delete ui;
}

//В РАЗРАБОТКЕ.
//Модуль администрирования, будет использоваться пользователями с правами администратора
//для управления созданными записями и предоставленными доступами.
//___________________________________________________________________________________________//

void moduleAdm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    if(index.column() < 2)
        return;
    else
    {
        addonAdmUserInfo *windowEdit = new addonAdmUserInfo();
        windowEdit->show();
        connect(windowEdit, &addonAdmUserInfo::signalSentData, this, &moduleAdm::slotReceiveData);
        connect(this, &moduleAdm::signalSentData, windowEdit, &addonAdmUserInfo::slotReceiveDataAddon);
        sentRow = index.row();
        sentId = ui->tableWidget->item(index.row(), 0)->text();

        emit signalSentData(ui->tableWidget->item(index.row(), 1)->text(), sentId, ui->tableWidget->item(index.row(), 4)->text(), ui->tableWidget->item(index.row(), 5)->text());
    }
}

void moduleAdm::updateTable()
{
    sqlQuery.exec("SELECT * FROM loginData");

    while(ui->tableWidget->rowCount())
        ui->tableWidget->removeRow(0);

    /*
     * Запрет на редактирование выбранного пользователя
     * Хотя бы один админ
     * Редактирование из аддона
     */

    int count = 0;
    while(sqlQuery.next())
    {
        sqlQueryRoles.exec("SELECT * FROM loginRole WHERE login='" + sqlQuery.value(sqlQuery.record().indexOf("login")).toString() + "'");
        sqlQueryRoles.next();

        ui->tableWidget->insertRow(count);
        ui->tableWidget->setItem(count, 0, new QTableWidgetItem(sqlQuery.value(sqlQuery.record().indexOf("id")).toString()));
        ui->tableWidget->setItem(count, 1, new QTableWidgetItem(sqlQuery.value(sqlQuery.record().indexOf("login")).toString()));
        ui->tableWidget->setItem(count, 2, new QTableWidgetItem("***"));
        ui->tableWidget->setItem(count, 3, new QTableWidgetItem(sqlQuery.value(sqlQuery.record().indexOf("is_enable")).toString() == "1" ? "Enable" : "Disable"));
        ui->tableWidget->setItem(count, 4, new QTableWidgetItem(sqlQuery.value(sqlQuery.record().indexOf("is_adm")).toString() == "1" ? "Admin" : "--"));
        ui->tableWidget->setItem(count, 5, new QTableWidgetItem(sqlQueryRoles.value(sqlQueryRoles.record().indexOf("roleId")).toString()));

        count++;
    }
}

void moduleAdm::slotReceiveData(QString newPass, QString roles, QString isAdm)
{
    if(newPass.size())
        sqlQueryRoles.exec("UPDATE loginData SET password ='" + newPass + "' WHERE id = '" + sentId + "'");

    isAdm = isAdm == "Admin" ? "1" : "0";
    sqlQueryRoles.exec("UPDATE loginData SET is_adm ='" + isAdm + "' WHERE id = '" + sentId + "'");

    updateTable();
}
