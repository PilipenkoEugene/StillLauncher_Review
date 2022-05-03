#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <auth.h>
#include <tabs.h>
#include <modulesqrt.h>
#include <modulesqr.h>
#include <moduleimplement.h>
#include <moduleadm.h>

#include <QApplication>
#include <QWidget>
#include <QTabWidget>

#include <QtAlgorithms>
#include <QTableWidgetItem>
#include <QtDebug>

#include <QString>
#include <QPair>
#include <QSet>
#include <vector>

#include <QFileInfo>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    struct dynamicMenuElementDescription {
      QString name;
      QString parent;
      QString type;
    };

    QMenuBar *userBar = new QMenuBar();
    QString login = "";
    vector<dynamicMenuElementDescription> dynamicMenu;
    dynamicMenuElementDescription element;
    vector<QPair<QString, QMenu*>> menuList;
    QSet<QString> checkElement;

public:

    //Блок парсинга строки из БД.
    //Переводит форматы из "A|B|C" в ["A", "B", "C"]
    vector<QString> parsePartsOfString(QString modules)
    {
        vector<QString> listOfModules;
        listOfModules.clear();

        while(modules.indexOf('|') != -1)
        {
            listOfModules.push_back(modules.mid(0, modules.indexOf('|')));
            modules.remove(0, modules.indexOf('|') + 1);
        }
        listOfModules.push_back(modules);

        return listOfModules;
    }
    //___________________________________________________________________________________________//

    //Вынесенный блок динамического создания Action'ов
    //Исопользуется лямбда-выражение для создание связи между сигналом без параметров
    //и функцией с параметром.
    QAction* createActionByName(QString name)
    {
        QAction *newAction = new QAction();
        newAction->setText(name.toUpper());
        connect(newAction, &QAction::triggered, this, [=](){
            slotFabriqObjects(name);
        });

        return newAction;
    }
    //___________________________________________________________________________________________//

    //Блок, который позволяет найти индекс родителя для указанного подменю
    unsigned long long findMenu(QString nameSub)
    {
        unsigned long long pointer = -1;
        for(unsigned long long i = 0; i < menuList.size(); i++)
            if(menuList[i].first == nameSub)
            {
                pointer = i;
                break;
            }
        return pointer;
    }
    //___________________________________________________________________________________________//

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotStartAuth();
    void on_modulesTabs_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;
    Auth *windowAuth;

signals:
    void runAdm(int id, QString log, QString pass, QString roleD);

public slots:
    void slotLoginStatus(int codeOfResult, QString loginAuth, QString rolesList);
    void slotFabriqObjects(QString moduleName);

};
#endif // MAINWINDOW_H
