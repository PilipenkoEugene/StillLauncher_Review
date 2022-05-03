#ifndef AUTH_H
#define AUTH_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <vector>

using namespace std;

namespace Ui {
class Auth;
}

class Auth : public QDialog
{
    Q_OBJECT

public:
    int statusLogin = 0;

public:
    explicit Auth(QWidget *parent = nullptr);
    ~Auth();

public slots:
    void on_buttonAuth_clicked();

    //Блок парсинга строки из БД.
    //Переводит форматы из "A|B|C" в ["A", "B", "C"]
    vector<QString> listOfRolesToAuth (QString modules)
    {
        vector<QString> listOfRoles;
        listOfRoles.clear();

        while(modules.indexOf('|') != -1)
        {
            listOfRoles.push_back(modules.mid(0, modules.indexOf('|')));
            modules.remove(0, modules.indexOf('|') + 1);
        }
        listOfRoles.push_back(modules);

        return listOfRoles;
    }
    //___________________________________________________________________________________________//

private:
    Ui::Auth *ui;
    QSqlDatabase loginData;

signals:
    void signalLoginStatus(int statusLogin, QString login, QString rolesList);

private slots:
    void on_buttonAuthLater_clicked();
};

#endif // AUTH_H
