//
// Created by irolup on 23/12/23.
//
#include <QApplication>
#include "Controller.h"
#include "Insta/Insta.h"
#include "Reddit/redditDialog.h"
#include "mainWindow/mainWindow.h"

Controller::Controller() {
    // Initialisation des parties du système si nécessaire
}

int Controller::startApplication(int argc, char **argv) {
    QApplication app(argc, argv);
    Window window;

    window.show();
    return app.exec();
}