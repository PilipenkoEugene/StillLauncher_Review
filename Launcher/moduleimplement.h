#ifndef MODULEIMPLEMENT_H
#define MODULEIMPLEMENT_H

#include <QWidget>

namespace Ui {
class moduleImplement;
}

class moduleImplement : public QWidget
{
    Q_OBJECT

public:
    explicit moduleImplement(QWidget *parent = nullptr);
    ~moduleImplement();

private slots:
    void on_buttonImplResult_clicked();

private:
    Ui::moduleImplement *ui;
};

#endif // MODULEIMPLEMENT_H
