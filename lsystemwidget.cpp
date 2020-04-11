#include "lsystemwidget.h"

#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <utility>
#include <QMouseEvent>

LsystemWidget::LsystemWidget(QImage image, QWidget *parent) : QWidget(parent), image_(std::move(image)) {
    setAttribute(Qt::WA_StaticContents);
}

void LsystemWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    auto rect = event->rect();
    painter.drawImage(rect, image_, rect);
}

void LsystemWidget::setImage() {
    image_ = lsystem_printer_.print(str_);
    resizeImage(&image_, size());
    qDebug() << image_.size() << ' ' << this->size() << '\n';
}

void LsystemWidget::resizeEvent(QResizeEvent *event) {
    if (width() > image_.width() || height() > image_.height()) {
        int newWidth = qMax(width() + 128, image_.width());
        int newHeight = qMax(height() + 128, image_.height());
        resizeImage(&image_, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void LsystemWidget::resizeImage(QImage *image, const QSize &newSize) {
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void LsystemWidget::mouseReleaseEvent(QMouseEvent *event) {
    lsystem_printer_.setPosition(event->localPos());
    setImage();
    update();
}

void LsystemWidget::setString(std::string const &s) {
    str_ = s;
}

const LsystemPrinter &LsystemWidget::getLsystemPrinter() const {
    return lsystem_printer_;
}
