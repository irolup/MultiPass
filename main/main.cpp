#include <QApplication>
#include "mainWindow/mainWindow.h"
#include "Controller.h"

int main(int argc, char **argv)
{
    Controller controller;
    return controller.startApplication(argc, argv);
}
