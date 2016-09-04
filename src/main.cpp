#include <iostream>

#include <QApplication>

#include "MyGlWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MyGlWindow window;
    window.show();

    return app.exec();
}
