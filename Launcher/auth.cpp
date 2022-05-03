#include "auth.h"
#include "ui_auth.h"

#include "QMessageBox"
#include <vector>
#include <set>

using namespace std;

Auth::Auth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Auth)
{
    ui->setupUi(this);
    setWindowTitle("Авторизация");

    loginData = QSqlDatabase::addDatabase("QSQLITE");
    loginData.setDatabaseName(УКАЖИТЕ ПУТЬ К БД В "");
    loginData.open();
}

Auth::~Auth()
{
    delete ui;
}

//Окно авторизации пользователя.
//Работая с БД передает в основное окно все доступы пользователя, его логин и статус авторизации.
//Основная часть этого модуля будет вынесена из пользовательского клиента для повышения безопасности. Вероятно, безопасность будет построена на MD5
void Auth::on_buttonAuth_clicked()
{
    statusLogin = 0;  //0 - skipped auth, 1 - log and pass are correct, 2 - incorrect pass else - incorrect login
    QSqlQuery qryLogin; //variable for requests from database
    QString log, pass;

    //По записи логина + пароля в таблице проверяется корректности авторизации и
    //разбивается на 3 потока (Успешная авторизация/Неверный пароль/Неверный логин)
    if(qryLogin.exec("SELECT * FROM loginData WHERE login='" + ui->lineLogin->text() + "'"))
    {
        qryLogin.next();

        log = qryLogin.value(qryLogin.record().indexOf("login")).toString();
        pass = qryLogin.value(qryLogin.record().indexOf("password")).toString();

        //Блок успешной авторизации
        if(ui->lineLogin->text() == log && ui->linePassword->text() == pass)
        {
            statusLogin = 1;
            qryLogin.exec("SELECT * FROM loginRole WHERE login='" + ui->lineLogin->text() + "'");
            qryLogin.next();

            vector<QString> rolesIDs = listOfRolesToAuth(qryLogin.value(qryLogin.record().indexOf("roleId")).toString());
            vector<QString> currentRoleCheck;
            set<QString> uniqRoles;
            QString rolesList = "";

            for(unsigned long long i = 0; i < rolesIDs.size(); i++)
            {
                qryLogin.exec("SELECT * FROM roleData WHERE roleId='" + rolesIDs[i] + "'");
                qryLogin.next();

                currentRoleCheck = listOfRolesToAuth(qryLogin.value(qryLogin.record().indexOf("rolesList")).toString());

                for(unsigned long long i = 0; i < currentRoleCheck.size(); i++)
                {
                    if(uniqRoles.find(currentRoleCheck[i]) == uniqRoles.end())
                    {
                        uniqRoles.insert(currentRoleCheck[i]);
                        rolesList += rolesList.size() ? '|' + currentRoleCheck[i] : currentRoleCheck[i];
                    }
                }
            }

            emit signalLoginStatus(statusLogin, ui->lineLogin->text(), rolesList);
            close();
            return;
        }
        //___________________________________________________________________________________________//

        //Блок неверного пароля (возможно дополнение функциональности)
        else if(ui->lineLogin->text() == log && ui->linePassword->text() != pass)
            statusLogin = 2;
        //___________________________________________________________________________________________//

        if(statusLogin == 2)
            QMessageBox::warning(this, "Error", "Wrong password");
        else
            QMessageBox::warning(this, "Error", "Login is incorrect");
   }
    //___________________________________________________________________________________________//
}
//___________________________________________________________________________________________//

//Возможность пропуска авторизации для открытия программы с базовым доступом к функциям.
//Базовые возможности будут дополняться.
void Auth::on_buttonAuthLater_clicked() //auth wasn't finished, skip button was triggerd
{
    statusLogin = 0;
    close();
    QMessageBox::warning(this, "Внимание", "Вы не вошли в свою запись. Функционал ограничен");
    emit signalLoginStatus(statusLogin, "Не авторизован", "");
    return;
}
//___________________________________________________________________________________________//

