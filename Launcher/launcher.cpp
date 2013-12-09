#include "launcher.h"
#include "ui_launcher.h"
#include <algorithm>

Launcher::Launcher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Launcher)
{
    ui->setupUi(this);

	// Set up UI
	this->setFixedSize(300, 210);
    windowed = false;
    ui->widthEntry->hide();
    ui->heightEntry->hide();
    ui->resolutionXLabel->hide();
    ui->resolutionWindowedLabel->hide();
    QRegExpValidator* resolutionValidator = new QRegExpValidator(QRegExp("[0-9]{3,4}"), this);
    ui->widthEntry->setValidator(resolutionValidator);
    ui->heightEntry->setValidator(resolutionValidator);

	// Enumerate supported fullscren modes
    glfwInit();
    int modeCount;
    const GLFWvidmode* glfwModes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &modeCount);
    for (int i = modeCount-1; i >= 0; i--)
    {
        // Minimum acceptable resolution 1024x720 (1280x720 usually, but cropping to 4:3 is possible)
        if (glfwModes[i].width >= 1024 and glfwModes[i].height >= 720)
        {
            addVideoMode(&modeList, glfwModes[i].width, glfwModes[i].height, glfwModes[i].refreshRate);
        }
    }
    glfwTerminate();

	// And add them to a list
    for (auto& mode : modeList)
    {
        QString modeString(QString::number(mode.width) + QString('x') + QString::number(mode.height));
        ui->resolutionBox->addItem(modeString);
    }
}

Launcher::~Launcher()
{
    delete ui;
}

void Launcher::on_windowedBox_toggled(bool checked)
{
    if (checked)
    {
        ui->resolutionBox->hide();
        ui->refreshBox->hide();
        ui->vsyncBox->setEnabled(false);
        ui->resolutionFullscreenLabel->hide();
        ui->widthEntry->show();
        ui->heightEntry->show();
        ui->resolutionXLabel->show();
        ui->resolutionWindowedLabel->show();
        ui->widthEntry->setText(QString::number(modeList[ui->resolutionBox->currentIndex()].width));
        ui->heightEntry->setText(QString::number(modeList[ui->resolutionBox->currentIndex()].height));
        windowed = true;
    }
    else
    {
        ui->resolutionBox->show();
        ui->refreshBox->show();
        ui->vsyncBox->setEnabled(true);
        ui->resolutionFullscreenLabel->show();
        ui->widthEntry->hide();
        ui->heightEntry->hide();
        ui->resolutionXLabel->hide();
        ui->resolutionWindowedLabel->hide();
        windowed = false;
    }
}

void Launcher::on_startButton_clicked()
{
    QMessageBox* msgBox = new QMessageBox(0);
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->setStandardButtons (QMessageBox::Ok);
    msgBox->setWindowTitle("The game");
    msgBox->setText("Allan, please add game");
    msgBox->setIcon(QMessageBox::Icon::Information);
    msgBox->setModal(false);
    msgBox->open(this, SIGNAL(destroyed()));
    this->close();
}

void Launcher::on_resolutionBox_currentIndexChanged(int index)
{
    ui->refreshBox->clear();
    for (auto& refresh : modeList[index].rates)
    {
        ui->refreshBox->addItem(QString::number(refresh));
    }
}
