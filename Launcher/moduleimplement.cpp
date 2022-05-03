#include "moduleimplement.h"
#include "ui_moduleimplement.h"

moduleImplement::moduleImplement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::moduleImplement)
{
    ui->setupUi(this);
}

moduleImplement::~moduleImplement()
{
    delete ui;
}

void moduleImplement::on_buttonImplResult_clicked()
{
    qreal a = ui->lineImplf->text().toDouble();
    qreal b = ui->lineImpls->text().toDouble();
    ui->labelImplResult->setText("Result: " + QString::number(a + b));
}

