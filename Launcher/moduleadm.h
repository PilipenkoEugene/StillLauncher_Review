#ifndef MODULEADM_H
#define MODULEADM_H

#include <QWidget>

namespace Ui {
class moduleAdm;
}

class moduleAdm : public QWidget
{
    Q_OBJECT

public slots:
    void run(int id, QString log, QString pass, QString roleD);

public:
    explicit moduleAdm(QWidget *parent = nullptr);
    ~moduleAdm();

private:
    Ui::moduleAdm *ui;
};

#endif // MODULEADM_H
