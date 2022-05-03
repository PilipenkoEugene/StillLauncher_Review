#ifndef MODULESQR_H
#define MODULESQR_H

#include <QWidget>

namespace Ui {
class moduleSqr;
}

class moduleSqr : public QWidget
{
    Q_OBJECT

public:
    explicit moduleSqr(QWidget *parent = nullptr);
    ~moduleSqr();

private slots:
    void on_buttonSqrResult_clicked();

private:
    Ui::moduleSqr *ui;
};

#endif // MODULESQR_H
