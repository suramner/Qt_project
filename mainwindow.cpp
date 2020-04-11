#include "infowidget.h"
#include "mainwindow.h"
#include "setupwidget.h"
#include "lsystemwidget.h"

#include <QDebug>
#include <QWidget>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto *vbox_layout_menu_ = new QVBoxLayout(this);
    auto *setup = new QPushButton("Setup");
    auto *examples = new QPushButton("Examples");
    auto info = new QPushButton("Info");
    auto *run = new QPushButton("Run");

    QObject::connect(setup, &QPushButton::released, this, &MainWindow::setSetup);
    QObject::connect(info, &QPushButton::released, this, &MainWindow::setInfo);
    QObject::connect(run, &QPushButton::released, this, &MainWindow::setRun);

    vbox_layout_menu_->addWidget(setup);
    vbox_layout_menu_->addWidget(examples);
    vbox_layout_menu_->addWidget(info);
    vbox_layout_menu_->addWidget(run);

    menu_ = new QWidget(this);
    menu_->setLayout(vbox_layout_menu_);
    menu_->show();

    info_ = new InfoWidget(this);
    info_->hide();

    setup_ = new SetupWidget(this);
    setup_->hide();

    run_ = new LsystemWidget(QImage(), this);
    run_->hide();

    output_ = info_;
    output_->show();

    this->setMinimumSize(500, 200);

    resize(this->size());
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    auto size = e->size();
    resize(size);
}

LSystem &MainWindow::lsystem()
{
    return setup_->lsystem();
}

const LSystem &MainWindow::lsystem() const
{
    return lsystem_;
}

const LsystemPrinter &MainWindow::lsystem_printer() const
{
    return run_->getLsystemPrinter();
}

MainWindow::~MainWindow()
{
    delete menu_;
    delete setup_;
    delete run_;
    delete info_;
}

void MainWindow::setSetup()
{
    switchToWidget(setup_);
}

void MainWindow::setInfo()
{
    switchToWidget(info_);
}

void MainWindow::setRun()
{
    run_->setString(lsystem().stringS());
    run_->setImage();
    switchToWidget(run_);
}

void MainWindow::resize(const QSize &size)
{
    resizeMenu(size);
    resizeOutput(size);
}

void MainWindow::resizeMenu(QSize const &size)
{
    menu_->resize(size.width() / 5, size.height());
}

void MainWindow::resizeOutput(const QSize &size)
{
    output_->setGeometry(menu_->width(), 0, size.width() - menu_->width(), size.height());
}

void MainWindow::switchToWidget(QWidget *w)
{
    output_->hide();
    output_ = w;
    resize(this->size());
    output_->show();
}

