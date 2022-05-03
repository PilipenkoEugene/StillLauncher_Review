#include "modulesqr.h"
#include "ui_modulesqr.h"

moduleSqr::moduleSqr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::moduleSqr)
{
    ui->setupUi(this);
}

moduleSqr::~moduleSqr()
{
    delete ui;
}

void moduleSqr::on_buttonSqrResult_clicked()
{
    qreal a = ui->lineSqr->text().toDouble();
    ui->labelSqrResult->setText("Result: " + QString::number(a * a));
}

