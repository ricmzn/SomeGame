#ifndef RESOURCECONVERTER_H
#define RESOURCECONVERTER_H

#include <QWidget>
#include <QFileDialog>
#include <QMimeDatabase>

namespace Ui {
    class ResourceConverter;
}

class ResourceConverter : public QWidget
{
        Q_OBJECT

    public:
        explicit ResourceConverter(QWidget* parent);
        ~ResourceConverter();

    private slots:
        void on_loadButton_clicked();

        void on_saveButton_clicked();

    private:
        Ui::ResourceConverter *ui;
        QPixmap previewImage;
};

#endif // RESOURCECONVERTER_H
