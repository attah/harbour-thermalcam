#ifndef THERMALIMAGE_H
#define THERMALIMAGE_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QImage>
#include <thread>
#include <functional>
#include <QDebug>

class ThermalImage : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QImage image READ getImage WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(bool valid READ isValid NOTIFY imageChanged)
public:
    ThermalImage();

    void paint(QPainter *painter);

signals:
    void imageChanged();

public slots:
    void doChangeImage()
    {
        update();
    }

private:
    QImage getImage() const;
    void setImage(const QImage &image);

    bool isValid() const;

    QImage _image;
    std::thread _thread;
};

#endif // THERMALIMAGE_H
