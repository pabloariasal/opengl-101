#include <GL/glew.h>
#include <iostream>

#include "MyGlWindow.h"

void MyGlWindow::initializeGL()
{
    glewInit();

    //Set vertices of initial 2D triangle in screen coordinates
    GLfloat vertices[] =
    {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    //Create and bind vertex buffer
    GLuint vertexBufferId;
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

    //Copy vertices to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Set attributes on data.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void MyGlWindow::paintGL()
{
    glViewport(0, 0, width(), height());

    //Draw entire vertex array, a total of three vertices that are interpreted as a triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
