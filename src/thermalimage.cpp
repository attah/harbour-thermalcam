#include "thermalimage.h"
#include <cpp-thermalcam/thermalcam.h>
#include <QStandardPaths>
#include <QDir>
#include <QImageWriter>
#include <QDateTime>

ThermalImage::ThermalImage()
{
    connect(this, &ThermalImage::visibleChanged, this, &ThermalImage::onVisibleChanged);

    _thread = std::thread([this]()
              {
                cv::VideoCapture captureDevice = find_camera();
                cv::Mat imageData;

                while(do_capture(captureDevice, imageData, 1920, 1080))
                {
                     QImage tmp = QImage(imageData.data, imageData.cols, imageData.rows, imageData.step1(), QImage::Format_RGB888).rgbSwapped();
                     _mutex.lock();
                    _image = tmp;
                    _mutex.unlock();
                    QMetaObject::invokeMethod(this, "doChangeImage", Qt::QueuedConnection);
                }
              });
}

void ThermalImage::paint(QPainter *painter)
{   
    qreal scale = std::min(boundingRect().height()/_image.height(), boundingRect().width()/_image.width());
    int x = (boundingRect().width()-_image.width()*scale)/(2*scale);
    int y = (boundingRect().height()-_image.height()*scale)/(2*scale);
    _mutex.lock();
    painter->scale(scale, scale);
    painter->drawImage(QPoint {x, y}, _image);
    _mutex.unlock();
}

void ThermalImage::save()
{
    QString PicturesPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QDir PicturesDir(PicturesPath);
    PicturesDir.mkdir("Thermal");
    QDateTime now = QDateTime::currentDateTime();
    QString nowStr = now.toString("yyyyMMdd_hhmmss");
    QString imagePath = PicturesPath + "/Thermal/ThermalImage_" + nowStr + ".png";
    QImageWriter writer(imagePath);
    _mutex.lock();
    writer.write(_image);
    _mutex.unlock();
}
