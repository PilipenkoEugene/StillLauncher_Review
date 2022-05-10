#ifndef ADDONADMUSERINFO_H
#define ADDONADMUSERINFO_H

#include <QWidget>
#include <moduleadm.h>

namespace Ui {
class addonAdmUserInfo;
}

class addonAdmUserInfo : public QWidget
{
    Q_OBJECT

public:
    explicit addonAdmUserInfo(QWidget *parent = nullptr);
    ~addonAdmUserInfo();

private:
    Ui::addonAdmUserInfo *ui;

public:
    bool admStat;
    QString newRoles, newPass = "";

private slots:
    void on_pushButton_clicked();

signals:
    void signalSentData(QString newPass, QString roles, QString isAdm);

public slots:
    void slotReceiveDataAddon(QString login, QString id, QString isAdm, QString roles);
};

#endif // ADDONADMUSERINFO_H
