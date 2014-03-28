#include "DataZipper.h"
#include "ui_DataZipper.h"

DataZipper::DataZipper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataZipper)
{
    ui->setupUi(this);
}

DataZipper::~DataZipper()
{
    delete ui;
}
