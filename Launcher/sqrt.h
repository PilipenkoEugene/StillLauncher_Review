#ifndef SQRT_H
#define SQRT_H

#include <QWidget>

namespace Ui {
class Sqrt;
}

class Sqrt : public QWidget
{
    Q_OBJECT

public:
    explicit Sqrt(QWidget *parent = nullptr);
    ~Sqrt();

private:
    Ui::Sqrt *ui;
};

#endif // SQRT_H
