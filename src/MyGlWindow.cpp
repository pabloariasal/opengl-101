#include <GL/glew.h>
#include <iostream>

#include "MyGlWindow.h"


void MyGlWindow::initializeGL()
{
    glewInit();


}

void MyGlWindow::paintGL()
{
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}
