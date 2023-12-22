#include <QApplication>
#include "mainWindow/mainWindow.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    Window Window;
    Window.show();

    return app.exec();
}
