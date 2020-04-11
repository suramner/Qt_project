#ifndef LSYSTEMWIDGET_H
#define LSYSTEMWIDGET_H

#include <QWidget>

#include <string>

#include "lsystemprinter.h"

class LsystemWidget : public QWidget
{
public:
    explicit LsystemWidget(QImage , QWidget *parent = nullptr);

    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void setImage();

    void setString(std::string const &);

    static void resizeImage(QImage *image, const QSize &newSize);

    [[nodiscard]] const LsystemPrinter &getLsystemPrinter() const;

private:
    LsystemPrinter lsystem_printer_;
    std::string str_;
    QImage image_;
};

#endif // LSYSTEMWIDGET_H
