#include "sqrt.h"
#include "ui_sqrt.h"

Sqrt::Sqrt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sqrt)
{
    ui->setupUi(this);
}

Sqrt::~Sqrt()
{
    delete ui;
}
