#ifndef MODULEADM_H
#define MODULEADM_H

#include <QWidget>
#include <QtSql>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <addonadmuserinfo.h>

namespace Ui {
class moduleAdm;
}

class moduleAdm : public QWidget
{
    Q_OBJECT

public:
    explicit moduleAdm(QWidget *parent = nullptr);
    ~moduleAdm();

public:
    QSqlDatabase loginData = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery sqlQuery, sqlQueryRoles;
    QString login;
    int sentRow;
    QString sentId;

    void updateTable();

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);

public slots:
    void slotReceiveData(QString newPass, QString roles, QString isAdm);

signals:
    void signalSentData(QString login, QString id, QString isAdm, QString roles);

private:
    Ui::moduleAdm *ui;
};

#endif // MODULEADM_H
