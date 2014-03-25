#include "ToolsWindow.h"
#include "ui_ToolsWindow.h"

ToolsWindow::ToolsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToolLauncher)
{
    ui->setupUi(this);
    ui->tabWidget->addTab(new ResourceConverter(this), "Resource Converter");
    ui->tabWidget->addTab(new ShaderViewer(this), "Shader Viewer");
}

ToolsWindow::~ToolsWindow()
{
    delete ui;
}
