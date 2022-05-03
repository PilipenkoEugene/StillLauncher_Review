#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->modulesTabs->addTab(new Tabs, QString("FAQ"));
    ui->modulesTabs->setTabsClosable(false);

    QSqlDatabase testdb=QSqlDatabase::addDatabase("QSQLITE");
    testdb.setDatabaseName(УКАЖИТЕ ПУТЬ К БД В "");

    setWindowTitle("Launcher");
    setStyleSheet("background-color: light gray");

    slotStartAuth();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Наиболее оптимальный способ создания объекта по имени в строковом представлении
//Данный формат оптимальнее абстрактной фабрики, тк не требует достройки фабричного метода
//и определения наследования. Регистрация класса заменяется условным оператором.
void MainWindow::slotFabriqObjects(QString moduleName)
{
    moduleName = moduleName.toUpper();

    //Эта часть позволяет переключиться на уже созданный модуль, если он все еще открыт,
    //чтобы не создавать копии. Можно добавлять гибкость, чтобы было возможно открыть несколько
    //копий одного модуля.
    foreach (QWidget* child, ui->modulesTabs->findChildren<QWidget*>())
        if (child->objectName() == moduleName && ui->modulesTabs->indexOf(child) != -1)
        {
            ui->modulesTabs->setCurrentIndex(ui->modulesTabs->indexOf(child));
            return;
        }
    //___________________________________________________________________________________________//

    //Часть, эквивалентная по размеру регистрации классов в фабрике, но более очевидная в написании
    QWidget* newTab;

    if(moduleName == "FAQ")  {newTab = new Tabs;}
    if(moduleName == "SQRT") {newTab = new moduleSqrt;}
    if(moduleName == "SQR")  {newTab = new moduleSqr;}
    if(moduleName == "IMPL") {newTab = new moduleImplement;}
    if(moduleName == "ADM")  {newTab = new moduleAdm;}
    //___________________________________________________________________________________________//

    newTab->setObjectName(moduleName);
    ui->modulesTabs->addTab(newTab, moduleName);
    ui->modulesTabs->setCurrentIndex(ui->modulesTabs->count() - 1);
    ui->modulesTabs->setTabsClosable(true);
}
//___________________________________________________________________________________________//

//Формирование конечного состояния окна для пользователя.
void MainWindow::slotLoginStatus(int codeOfResult, QString loginAuth, QString rolesList)
{
    //Перевод основного окна в начальное состояние. Очистка всех bar'ов, добавление меню пользователя и начальной вкладки FAQ. Запрет на закрытие вкладок.
    //Здесь можно добавлять все возможности для неавторизованных пользователей.
    dynamicMenu.clear();
    menuList.clear();
    checkElement.clear();

    ui->menubar->clear();
    userBar->clear();
    ui->toolBar->clear();
    ui->modulesTabs->clear();
    ui->modulesTabs->setTabsClosable(false);

    QMenu *userMenu = new QMenu(loginAuth, userBar);
    userBar->addMenu(userMenu);
    ui->menubar->setCornerWidget(userBar);

    ui->modulesTabs->addTab(new Tabs, QString("FAQ"));

    QAction *logInAction = new QAction("Войти");
    connect(logInAction, &QAction::triggered, this, [=](){
        windowAuth = new Auth();
        windowAuth->show();
        connect(windowAuth, &Auth::signalLoginStatus, this, &MainWindow::slotLoginStatus);
    });
    userMenu->addAction(logInAction);

    QAction *exitAction = new QAction("Выйти");
    connect(exitAction, &QAction::triggered, this, [=](){QApplication::quit();});
    userMenu->addAction(exitAction);

    show();

    //___________________________________________________________________________________________//

    //Создание всех bar'ов для конкретного авторизованного пользователя
    //Создание динамического меню
    if(codeOfResult == 1)
    {
        logInAction->setText("Сменить пользователя");

        //Создание первичной иерархии меню. Пока БД должна находится на устройстве пользователя,
        //но в дальнейшем будет перенесена на сервер. listOfModules хранит список всех модулей,
        //доступных пользователю.
        vector<QString> listOfModules = parsePartsOfString(rolesList);
        checkElement.clear();
        //___________________________________________________________________________________________//

        //В dynamicMenu создается список структур
        //{Name (QString), Parent/"Main" (QString), Type (QString}
        //В menuList создается список структур
        //{Name (QString, QMenu*}
        sort(listOfModules.begin(), listOfModules.end());
        for(unsigned long long i = 0; i < listOfModules.size(); i++)
        {
            ui->toolBar->addAction(createActionByName(listOfModules[i]));

            QSqlQuery qryActionPath;
            qryActionPath.exec("SELECT * FROM actionPath WHERE action='" + listOfModules[i] + "'");
            qryActionPath.next();

            vector<QString> partsOfPath = parsePartsOfString(qryActionPath.value(qryActionPath.record().indexOf("path")).toString());

            for(unsigned long long j = 0; j < partsOfPath.size(); j++)
            {
                element.name = partsOfPath[j];
                element.type = j != partsOfPath.size() -1 ? "QMenu" : "QAction";
                element.parent = !j ? partsOfPath[j], "Main" : partsOfPath[j - 1];

                if(element.type == "QMenu")
                {
                    if(checkElement.find(partsOfPath[j]) == checkElement.end())
                    {
                        checkElement.insert(partsOfPath[j]);
                        QMenu *newMenu = new QMenu;
                        newMenu->setTitle(partsOfPath[j]);
                        dynamicMenu.push_back(element);
                        menuList.push_back(make_pair(partsOfPath[j], newMenu));
                    }
                }
                else
                    dynamicMenu.push_back(element);
            }
        }
        //___________________________________________________________________________________________//

        //В приведенном блоке выполняется отрисовка меню по готовой структуре.
        //Вкладки типа Main отрисовываются сразу, все остальные элементы последовательно
        //добавляются в своих родителей.
        for(unsigned long long i = 0; i < dynamicMenu.size(); i++)
        {
            element = dynamicMenu[i];
            if(element.parent != "Main")
            {
                for(unsigned long long j = 0; j < menuList.size(); j++)
                {
                    if(menuList[j].first == element.parent)
                    {
                        if(element.type == "QMenu")
                            menuList[j].second->addMenu(menuList[findMenu(element.name)].second);
                        else
                            menuList[j].second->addAction(createActionByName(element.name));
                        break;
                    }
                }
            }
            else
                ui->menubar->addMenu(menuList[findMenu(element.name)].second);
        }
        //___________________________________________________________________________________________//
    }
    //___________________________________________________________________________________________//
}
//___________________________________________________________________________________________//

//Организация работы закрытия вкладок.
//Если закрыть последнюю, то откроется FAQ, которую нельзя закрыть до открытия второй
void MainWindow::on_modulesTabs_tabCloseRequested(int index)
{
    ui->modulesTabs->removeTab(index);
    if(!ui->modulesTabs->count())
    {
        slotFabriqObjects("faq");
        ui->modulesTabs->setTabsClosable(false);
    }
}
//___________________________________________________________________________________________//


//Подключение авторизации.
void MainWindow::slotStartAuth()
{
    windowAuth = new Auth();
    windowAuth->show();
    connect(windowAuth, &Auth::signalLoginStatus, this, &MainWindow::slotLoginStatus);
}
//___________________________________________________________________________________________//
