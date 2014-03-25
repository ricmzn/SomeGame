#include "ResourceConverter.h"
#include "ui_ResourceConverter.h"

ResourceConverter::ResourceConverter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResourceConverter)
{
    ui->setupUi(this);
    ui->saveButton->setEnabled(false);
}

ResourceConverter::~ResourceConverter()
{
    delete ui;
}

void ResourceConverter::on_loadButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Open file...", "../Data", "(*.bmp *.png *.tga)");
    if (!file.isEmpty())
    {
        QFileInfo fileInfo(file);
        QString clampedName = "Textures/" + fileInfo.baseName() + ".texture";
        ui->saveLineEdit->setText(clampedName);
        ui->statusMessage->setText("Ready");
        previewImage.load(file);
        int width = ui->label->width();
        int height = ui->label->height();
        ui->label->setPixmap(previewImage.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->saveButton->setEnabled(true);
    }
}

void ResourceConverter::on_saveButton_clicked()
{
    ui->statusMessage->setTextFormat(Qt::RichText);
    ui->statusMessage->setText("<b>" + ui->saveLineEdit->text() + "</b> saved successfully!");
}
