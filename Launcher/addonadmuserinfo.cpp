#include "addonadmuserinfo.h"
#include "ui_addonadmuserinfo.h"

addonAdmUserInfo::addonAdmUserInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addonAdmUserInfo)
{
    ui->setupUi(this);
}

addonAdmUserInfo::~addonAdmUserInfo()
{
    delete ui;
}

void addonAdmUserInfo::on_pushButton_clicked()
{
    newRoles = ui->lineRoles->text();
    admStat = ui->checkBoxIsAdm->isChecked();
    newPass = ui->linePassword->text();

    emit signalSentData(newPass, newRoles, admStat ? "Admin" : "--");
    close();
}

void addonAdmUserInfo::slotReceiveDataAddon(QString login, QString id, QString isAdm, QString roles)
{
    ui->lineLogin->setText(login);
    ui->lineLogin->setEnabled(0);

    ui->lineId->setText(id);
    ui->lineId->setEnabled(0);

    ui->lineRoles->setText(roles);
    ui->lineRoles->setEnabled(0);

    QMessageBox::warning(this, "", isAdm);
    if(isAdm == "Admin")
    {
        ui->checkBoxIsAdm->setChecked(true);
        admStat = 1;
    }
    else
    {
        ui->checkBoxIsAdm->setChecked(false);
        admStat = 0;
    }
}

