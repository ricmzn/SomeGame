#include "ShaderViewer.h"
#include "ui_ShaderViewer.h"

ShaderViewer::ShaderViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShaderViewer)
{
    ui->setupUi(this);
}

ShaderViewer::~ShaderViewer()
{
    delete ui;
}
