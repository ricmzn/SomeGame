#include "ToolWindow.h"
#include "ui_ToolWindow.h"

ToolWindow::ToolWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToolLauncher)
{
    ui->setupUi(this);
    ui->tabWidget->addTab(new ResourceConverter(this), "Resource Converter");
}

ToolWindow::~ToolWindow()
{
    delete ui;
}

void ToolWindow::runGame()
{
    qApp->exit(1);
}
