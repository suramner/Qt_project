#include "setupwidget.h"

#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>

SetupWidget::SetupWidget(QWidget *parent) : QWidget(parent) {
    auto *mainwidget = new QWidget(this);
    widget_ = new QVBoxLayout(this);
    input_ = new QTextEdit(this);
    input_start_ = new QTextEdit(this);
    output_rules_ = new QPlainTextEdit(this);
    output_rules_->setReadOnly(true);
    auto *button = new QPushButton("Add rule", this);
    auto *button_start = new QPushButton("Set start", this);
    auto *button_update = new QPushButton("Update", this);
    auto *button_clear = new QPushButton("Clear", this);

    QObject::connect(button, &QPushButton::released, this, &SetupWidget::addRule);
    QObject::connect(button_start, &QPushButton::released, this, &SetupWidget::setStart);
    QObject::connect(button_update, &QPushButton::released, this, &SetupWidget::updateLSystem);
    QObject::connect(button_clear, &QPushButton::released, this, &SetupWidget::clear);

    input_->setFixedSize(100, 30);
    input_start_->setFixedSize(100, 30);
    widget_->addWidget(input_start_);
    widget_->addWidget(button_start);
    widget_->addWidget(input_);
    widget_->addWidget(button);
    widget_->addWidget(button_update);
    widget_->addWidget(button_clear);
    widget_->addWidget(output_rules_);
    mainwidget->setLayout(widget_);
}

void SetupWidget::addRule() {
    if (lsystem_.ParseRule(input_->toPlainText().toStdString())) {
        output_rules_->moveCursor(QTextCursor::End);
        output_rules_->insertPlainText(input_->toPlainText() + "\n");
        output_rules_->moveCursor(QTextCursor::End);
    }
    input_->setText("");
}

LSystem &SetupWidget::lsystem() {
    return lsystem_;
}

LSystem const &SetupWidget::lsystem() const {
    return lsystem_;
}

void SetupWidget::setStart() {
    lsystem_.SetString(input_start_->toPlainText().toStdString());
    input_start_->setReadOnly(true);
}

void SetupWidget::updateLSystem() {
    lsystem_.Update();
}

void SetupWidget::clear() {
    lsystem_ = LSystem();
    input_start_->setReadOnly(false);
    input_start_->clear();
    output_rules_->clear();
    input_->clear();
}
