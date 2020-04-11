#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    LSystem lsystem("-F",
                    LSystem::MapOneRuleType{}, LSystem::MapNoRuleType{{'F', [](char) {
                return "F+F-F-F+F";
            }},
                                                                      {
                                                                       '+', [](char) {
                                                                          return "+";
                                                                      }
                                                                      },
                                                                      {'-', [](char) {
                                                                          return "-";
                                                                      }}});
    lsystem.Update();
    lsystem.Update();
    lsystem.Update();
//    w.lsystem() = lsystem;
    return a.exec();
}
