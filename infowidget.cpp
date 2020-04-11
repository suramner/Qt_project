#include "infowidget.h"

#include <QTextEdit>
#include <QDebug>
#include <QFile>

InfoWidget::InfoWidget(QWidget *parent) : QTextEdit(parent) {
    QFile file = QFile("/Users/linuxoid/CLionProjects/Qt/resources/info.md");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can't open /Users/linuxoid/CLionProjects/Qt/resources/info.md\n";
        return;
    }
    this->setMarkdown(file.readAll());
    this->setReadOnly(true);
    this->show();
    file.close();
}
