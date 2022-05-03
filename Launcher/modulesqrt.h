#ifndef MODULESQRT_H
#define MODULESQRT_H

#include <QWidget>

namespace Ui {
class moduleSqrt;
}

class moduleSqrt : public QWidget
{
    Q_OBJECT

public:
    explicit moduleSqrt(QWidget *parent = nullptr);
    ~moduleSqrt();

private slots:
    void on_buttonSqrtResult_clicked();

private:
    Ui::moduleSqrt *ui;
};

#endif // MODULESQRT_H
