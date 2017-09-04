#include <GL/glew.h>
#include <iostream>

#include <boost/filesystem.hpp>

#include "my_gl_window.h"
#include "shader_compiler.h"

void MyGlWindow::initializeGL()
{
	namespace fs = boost::filesystem;

    glewInit();

    //Set vertices of triangles (We just render two triangles)
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

    //Copy defined vertices to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Set attributes on data. In this case we require a single attribute: vertex location.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Setup vertex ids
    GLushort indices[] = {0, 1, 2, 3, 4, 2};

    GLuint indexBufferId;
    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Assuming executable is run in project_root/build
    fs::path shader_dir = boost::filesystem::current_path().parent_path() / fs::path("shaders");

    fs::path vertex_shader_file = shader_dir / fs::path("vertex_shader.glsl");
    fs::path fragment_shader_file = shader_dir / fs::path("fragment_shader.glsl");

    if(!fs::exists(vertex_shader_file) || !fs::exists(fragment_shader_file))
    {
        std::cerr << "Shaders couldn't be found. Please make sure that you run the executable in the directory opengl-101/build" << std::endl;
        exit(EXIT_FAILURE);
    }
	
	//Compile and install the shaders
    GLuint program = installShaders(vertex_shader_file.string(), fragment_shader_file.string());

    glUseProgram(program);
}

void MyGlWindow::paintGL()
{
    glViewport(0, 0, width(), height());

    //Draw elements defined in the element buffer
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}
