#ifndef THERMALIMAGE_H
#define THERMALIMAGE_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QImage>
#include <thread>
#include <functional>
#include <QDebug>
#include <mutex>

class ThermalImage : public QQuickPaintedItem
{
    Q_OBJECT

public:
    ThermalImage();

    void paint(QPainter *painter);

    Q_INVOKABLE void save();

signals:
    void imageChanged();

public slots:
    void doChangeImage()
    {
        update();
    }

    void onVisibleChanged()
    {
        if(!isVisible())
        {
            _mutex.lock();
        }
        else
        {
            _mutex.unlock();
        }
    }

private:

    QImage _image;
    std::thread _thread;
    std::mutex _mutex;
};

#endif // THERMALIMAGE_H
