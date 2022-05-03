#include "modulesqrt.h"
#include <QtMath>
#include "ui_modulesqrt.h"

moduleSqrt::moduleSqrt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::moduleSqrt)
{
    ui->setupUi(this);
}

moduleSqrt::~moduleSqrt()
{
    delete ui;
}

void moduleSqrt::on_buttonSqrtResult_clicked()
{
    qreal a = ui->lineSqrt->text().toDouble();
    ui->labelSqrtResult->setText("Result: " + QString::number(qSqrt(a)));
}

