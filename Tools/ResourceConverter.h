#ifndef RESOURCECONVERTER_H
#define RESOURCECONVERTER_H

#include <QWidget>

namespace Ui {
    class ResourceConverter;
}

class ResourceConverter : public QWidget
{
        Q_OBJECT

    public:
        explicit ResourceConverter(QWidget *parent = 0);
        ~ResourceConverter();

    private:
        Ui::ResourceConverter *ui;
};

#endif // RESOURCECONVERTER_H
