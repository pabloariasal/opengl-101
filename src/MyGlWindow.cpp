#include <GL/glew.h>
#include <iostream>

#include "MyGlWindow.h"

#include "ShaderInstaller.h"
#include <boost/program_options.hpp>

namespace fs = boost::filesystem;

void MyGlWindow::initializeGL()
{
    glewInit();

    //Set vertices of triangles
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

    //Assuming executable is run in project_root/build
    fs::path shader_dir = boost::filesystem::current_path().parent_path() / fs::path("shaders");

    fs::path vertex_shader_file = shader_dir / fs::path("vertex_shader.glsl");
    fs::path fragment_shader_file = shader_dir / fs::path("fragment_shader.glsl");

    if(!fs::exists(vertex_shader_file) || !fs::exists(fragment_shader_file))
    {
        std::cerr << "Shaders directory couldn't be found. Expected files: "
                  << vertex_shader_file.string() << " and "
                  << fragment_shader_file.string() <<
                    "Exiting." << std::endl;
        exit(1);
    }

    ShaderInstaller installer;
    GLuint program = installer.installShaders(vertex_shader_file, fragment_shader_file);

    glUseProgram(program);
}

void MyGlWindow::paintGL()
{
    glViewport(0, 0, width(), height());

    //Draw elements defined in the element buffer
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}
