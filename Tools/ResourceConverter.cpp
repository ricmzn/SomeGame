#include "ResourceConverter.h"
#include "ui_ResourceConverter.h"

ResourceConverter::ResourceConverter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResourceConverter)
{
    ui->setupUi(this);
    ui->saveButton->setEnabled(false);
    ui->saveLineEdit->setEnabled(false);
}

ResourceConverter::~ResourceConverter()
{
    delete ui;
}

void ResourceConverter::on_loadButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Open file...", QDir::homePath(), "(*.bmp *.png *.tga)");
    if (!file.isEmpty())
    {
        QFileInfo fileInfo(file);
        QString clampedName = "Textures/" + fileInfo.baseName() + ".texture";
        ui->saveLineEdit->setText(clampedName);
        //ui->statusMessage->setText("Ready");
        previewImage.load(file);
        int width = ui->previewLabel->width();
        int height = ui->previewLabel->height();
        ui->previewLabel->setPixmap(previewImage.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->saveButton->setEnabled(true);
        ui->saveLineEdit->setEnabled(true);

        QMimeDatabase mimeDatabase;
        QMimeType mimeType = mimeDatabase.mimeTypeForFile(file);
        ui->statusMessage->setText(mimeType.comment());
    }
}

void ResourceConverter::on_saveButton_clicked()
{
    ui->statusMessage->setTextFormat(Qt::RichText);
    ui->statusMessage->setText("<b>" + ui->saveLineEdit->text() + "</b> saved successfully!");
}
