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

                while(do_capture(captureDevice, imageData, boundingRect().width(), boundingRect().height()))
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
    int x = (boundingRect().width()-_image.width())/2;
    int y = (boundingRect().height()-_image.height())/2;
    _mutex.lock();
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
