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
    format.setSwapInterval(1);
    ui->glFrame->layout()->addWidget(new ShaderGLWidget(format, this));
}

ShaderViewer::~ShaderViewer()
{
    delete ui;
}
