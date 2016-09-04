#include <GL/glew.h>
#include <iostream>

#include "MyGlWindow.h"

void MyGlWindow::initializeGL()
{
    glewInit();

    //Set vertices of initial 2D triangle in screen coordinates
    GLfloat vertices[] =
    {
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
         0.0f,  0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
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

    //Indices
    GLushort indices[] = {0, 1, 2, 3, 4, 2};

    GLuint indexBufferId;
    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void MyGlWindow::paintGL()
{
    glViewport(0, 0, width(), height());

    //Draw elements defined in the element buffer
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}
