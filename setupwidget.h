#ifndef SETUPWIDGET_H
#define SETUPWIDGET_H

#include <QWidget>
#include "lsystem.h"

class QVBoxLayout;

class QTextEdit;

class QPlainTextEdit;

class SetupWidget : public QWidget {
public:
    explicit SetupWidget(QWidget *parent = nullptr);

    LSystem &lsystem();

    [[nodiscard]] LSystem const &lsystem() const;

    //void paintEvent(QPaintEvent *event) override;

private slots:
    void addRule();
    void setStart();
    void updateLSystem();

private:
    QVBoxLayout *widget_;
    QTextEdit *input_;
    QTextEdit *input_start_;
    QPlainTextEdit *output_rules_;
    LSystem lsystem_;
};

#endif // SETUPWIDGET_H
