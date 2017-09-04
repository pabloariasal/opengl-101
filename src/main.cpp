#include <QApplication>
#include "my_gl_window.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MyGlWindow window;
    window.show();

    return app.exec();
}
