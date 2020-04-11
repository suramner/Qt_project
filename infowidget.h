#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>
#include <QTextEdit>

class InfoWidget : public QTextEdit
{
public:
    explicit InfoWidget(QWidget *parent = nullptr);
};

#endif // INFOWIDGET_H
