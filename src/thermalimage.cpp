#include "thermalimage.h"
#include <cpp-thermalcam/thermalcam.h>

ThermalImage::ThermalImage()
{
    _thread = std::thread([this]()
              {
                cv::VideoCapture captureDevice = find_camera();
                cv::Mat imageData;

                while(do_capture(captureDevice, imageData, boundingRect().width(), boundingRect().height()))
                {
                    _image = QImage(imageData.data, imageData.cols, imageData.rows, imageData.step1(), QImage::Format_RGB888).rgbSwapped();
                    QMetaObject::invokeMethod(this, "doChangeImage", Qt::QueuedConnection);
                }
              });
}

void ThermalImage::paint(QPainter *painter)
{   
    int x = (boundingRect().width()-_image.width())/2;
    int y = (boundingRect().height()-_image.height())/2;
    painter->drawImage(QPoint {x, y}, _image);
}

QImage ThermalImage::getImage() const
{
    return _image;
}

void ThermalImage::setImage(const QImage &image)
{
    _image = image;
    emit imageChanged();
    update();
}

bool ThermalImage::isValid() const
{
    return !_image.isNull();
}
