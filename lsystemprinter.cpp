#include "lsystemprinter.h"

#include <string>

#include <QPainter>
#include <QRect>

#include <iostream>

#define _USE_MATH_DEFINES

#include <cmath>

LsystemPrinter::LsystemPrinter(QWidget *parent) : QWidget(parent), image_(1550, 1050, QImage::Format_RGB32) {
    setAttribute(Qt::WA_StaticContents);
}

QImage LsystemPrinter::print(std::string const &stringS_) {
    auto save = state_;
    clear();
    for (std::string::size_type i = 0; i < stringS_.size(); i++) {
        char c = stringS_[i];

        string s{};
        if (stringS_[i + 1] == '(') {
            auto it = map_one_rule_.at(c);
            bool ret = false;
            auto id = stringS_.find_first_of(')', i);
            if (id == string::npos) {
                throw std::runtime_error("no ).");
            }
            string sub = stringS_.substr(i + 2, (id - i - 1));
            int k = std::stoi(sub);
            for (auto j = it.begin(); !ret && j != it.end(); ++j) {
                (*j)(*this, c, ret, k);
            }
            i = id;
        } else {
            auto it = map_no_rule_.at(c);
            it(*this, c);
        }
    }
    state_ = save;

    return image_;
}

void LsystemPrinter::setPenWidth(int w) {
    state_.pen_width_ = w;
}

void LsystemPrinter::setColor(const QColor &c) {
    state_.color_ = c;
}

void LsystemPrinter::setDirection(const Vector &v) {
    state_.direction_ = v;
}

void LsystemPrinter::setLineSize(int s) {
    state_.line_size_ = s;
}

void LsystemPrinter::printLine() {
    QPainter painter(&image_);
    QPointF begin = state_.position_;
    QPointF end = state_.position_ + state_.direction_ * state_.line_size_;
    painter.setPen(QPen(state_.color_, state_.pen_width_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(begin, end);
    int rad = (state_.pen_width_ / 2) + 2;
    update(QRect(qpointFToQPoint(begin), qpointFToQPoint(end)).normalized().adjusted(-rad, -rad, +rad, +rad));
    state_.position_ = end;
}

void LsystemPrinter::go() {
    state_.position_ += state_.direction_ * state_.line_size_;
}

void LsystemPrinter::rotateLeft() {
    state_.direction_ = Vector{-state_.direction_.y, state_.direction_.x};
}

void LsystemPrinter::rotateRight() {
    state_.direction_ = Vector{state_.direction_.y, -state_.direction_.x};
}

void LsystemPrinter::rotate(double rad) {
    auto x = std::cos(rad) * state_.direction_.x - std::sin(rad) * state_.direction_.y;
    auto y = std::cos(rad) * state_.direction_.y + std::sin(rad) * state_.direction_.x;
    state_.direction_ = Vector{x, y};
}

void LsystemPrinter::rotate180() {
    state_.direction_ = Vector{-state_.direction_.x, -state_.direction_.y};
}

void LsystemPrinter::clear() {
    image_.fill(qRgb(255, 255, 255));
}

void LsystemPrinter::setPosition(QPointF const &p) {
    state_.position_ = p;
}

Vector operator*(const Vector &v, int a) {
    return {v.x * a, v.y * a};
}

Vector operator*(int a, const Vector &v) {
    return v * a;
}

QPoint qpointFToQPoint(const QPointF &qf) {
    return QPoint(qf.x(), qf.y());
}

ostream &operator<<(ostream &os, const Vector &v) {
    os << v.x << ' ' << v.y << '\n';
    return os;
}
