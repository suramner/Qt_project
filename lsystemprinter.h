#ifndef LSYSTEMPRINTER_H
#define LSYSTEMPRINTER_H


#include "lsystem.h"

#include <QWidget>

struct Vector {
    Vector(qreal x_, qreal y_) : x(x_), y(y_) {}

    qreal x = 0.;
    qreal y = 0.;

    operator QPointF() {
        return QPointF(x, y);
    }
};

Vector operator*(Vector const&, int);
Vector operator*(int, Vector const&);
std::ostream &operator<<(std::ostream&, Vector const&);

QPoint qpointFToQPoint(QPointF const &);

class LsystemPrinter : public QWidget
{
    Q_OBJECT
public:
    using OneRuleType = function<void(LsystemPrinter&, char, bool&, int)>;
    using NoRuleType = function<void(LsystemPrinter&, char)>;
    using MapOneRuleType = map<char, vector<OneRuleType>>;
    using MapNoRuleType = map<char, NoRuleType>;

    explicit LsystemPrinter(QWidget *parent = nullptr);

    QImage print(std::string const &);

    void setPosition(QPointF const &);

    void setPenWidth(int);

    void setColor(QColor const &);

    void setDirection(Vector const &);

    void setLineSize(int);

    void printLine();

    void go();

    void rotateLeft();

    void rotateRight();

    void rotate(double rad);

    void rotate180();

private:
    void clear();

    QImage image_;
    struct State {
        int pen_width_ = 2;
        int line_size_ = 20;
        QColor color_ = Qt::blue;
        QPointF position_ = {500., 250.};
        Vector direction_ = {0., -1.};
    } state_;
    MapNoRuleType map_no_rule_ = {
        {'F', [](LsystemPrinter &l, char) {
            l.printLine();
        }},
        {'f', [](LsystemPrinter &l, char) {
                 l.go();
        }},
        {'+', [](LsystemPrinter &l, char) {
             l.rotateLeft();
    }},
        {'-', [](LsystemPrinter &l, char) {
             l.rotateRight();
    }},
        {'|', [](LsystemPrinter &l, char) {
             l.rotate180();
    }}
    };
    MapOneRuleType map_one_rule_;
};

#endif // LSYSTEMPRINTER_H
