#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lsystem.h"
#include "lsystemprinter.h"

#include <QMainWindow>

class QVBoxLayout;
class InfoWidget;
class SetupWidget;
class LsystemWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent*) override;
    LSystem &lsystem();
    [[nodiscard]] LSystem const &lsystem() const;

    [[nodiscard]] LsystemPrinter const &lsystem_printer() const;
    ~MainWindow() override;


private slots:
    void setSetup();
    void setInfo();
    void setRun();

private:
    void resize(QSize const &);
    void resizeMenu(QSize const&);
    void resizeOutput(QSize const&);
    void switchToWidget(QWidget *);

    LSystem lsystem_;

    QWidget *menu_;
    QWidget *output_;
    InfoWidget *info_;
    SetupWidget *setup_;
    LsystemWidget *run_;
};
#endif // MAINWINDOW_H
