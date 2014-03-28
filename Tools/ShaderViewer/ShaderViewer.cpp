#include "ShaderViewer.h"
#include "ui_ShaderViewer.h"

ShaderViewer::ShaderViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShaderViewer)
{
    ui->setupUi(this);

    if (!QGLFormat::openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_4_0))
    {
        QMessageBox::critical(this, "Fatal Error",
                              "OpenGL 4.0 is not supported on this computer");
        std::exit(1);
    }
    QGLFormat format;
    format.setVersion(4, 0);
    format.setProfile(QGLFormat::CoreProfile);
    format.setSampleBuffers(1);
    format.setSamples(4);
    format.setSwapInterval(1);
    ui->glFrame->layout()->addWidget(new ShaderGLWidget(format, this));
    for (int i = 0; i < 30; i++)
    {
        ui->uniformWidget->layout()->addWidget(new QPushButton(this));
    }
}

ShaderViewer::~ShaderViewer()
{
    delete ui;
}
