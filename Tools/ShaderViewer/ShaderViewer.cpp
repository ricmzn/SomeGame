#include "ShaderViewer.h"
#include "ui_ShaderViewer.h"

ShaderViewer::ShaderViewer(QWidget* parent) :
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
    glWidget = new ShaderGLWidget(format, this);
    ui->glFrame->layout()->addWidget(glWidget);

    connect(glWidget, SIGNAL(contextReady()), this, SLOT(fillUniformList()));
}

ShaderViewer::~ShaderViewer()
{
    delete ui;
}

void ShaderViewer::on_modelSelector_clicked()
{
    QFileDialog::getOpenFileName(this, "Open Model", "../Data");
}

void ShaderViewer::on_wireframeBox_stateChanged(int arg1)
{
    if (arg1)
    {
        glWidget->setWireframe(true);
    }
    else
    {
        glWidget->setWireframe(false);
    }
}

void ShaderViewer::fillUniformList()
{
    const QList<Uniform>& uniforms = glWidget->getUniforms();
    for (const Uniform& uniform : uniforms)
    {
        switch(uniform.type)
        {
            default:
                QPushButton* button = new QPushButton(this);
                button->setText(uniform.name);
                ui->uniformWidget->layout()->addWidget(button);
                break;
        }
    }
}
