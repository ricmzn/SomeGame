#ifndef DATAZIPPER_H
#define DATAZIPPER_H

#include <QWidget>

namespace Ui {
    class DataZipper;
}

class DataZipper : public QWidget
{
        Q_OBJECT

    public:
        explicit DataZipper(QWidget* parent);
        ~DataZipper();

    private:
        Ui::DataZipper* ui;
};

#endif // DATAZIPPER_H
