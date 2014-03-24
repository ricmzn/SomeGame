#include "ResourceConverter.h"
#include "ui_ResourceConverter.h"

ResourceConverter::ResourceConverter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResourceConverter)
{
    ui->setupUi(this);
}

ResourceConverter::~ResourceConverter()
{
    delete ui;
}
