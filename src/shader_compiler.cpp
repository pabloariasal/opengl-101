#include "shader_compiler.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

std::string readTextFile(const std::string& file_path)
{
    std::ifstream file(file_path);
    std::stringstream ss;

    if(file.is_open())
    {
        ss << file.rdbuf(); // read entire file
    }
    else
    {
        std::cerr << "Could not open file " << file_path << std::endl;
    }

    file.close();

    return ss.str();
}

GLint checkCompileStatus(GLuint shader_id)
{
    GLint result = GL_FALSE;
    int InfoLogLength;

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(shader_id, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cerr << &VertexShaderErrorMessage[0] << std::endl;
    }

    return result;
}

GLuint installShaders(const std::string& vertex_shader, const std::string& fragment_shader)
{

    //Read shaders from text file
    std::string vertex_source = readTextFile(vertex_shader);
    std::string fragment_source = readTextFile(fragment_shader);

    //Create shaders
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    //Compile shaders
    const char* vertex_source_ptr = vertex_source.c_str();
    glShaderSource(vertex_shader_id, 1, &vertex_source_ptr, NULL);
    glCompileShader(vertex_shader_id);

    const char* fragment_source_ptr = fragment_source.c_str();
    glShaderSource(fragment_shader_id, 1, &fragment_source_ptr, NULL);
    glCompileShader(fragment_shader_id);

    //Check compile status
    if(!checkCompileStatus(vertex_shader_id) || !checkCompileStatus(fragment_shader_id))
    {
        std::cerr << "Error occurred while compiling the shaders. Exiting." << std::endl;
        exit(EXIT_FAILURE);
    }

    //Link program
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    // Check the program
    GLint result = GL_FALSE;
    int InfoLogLength;

    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if(InfoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(program_id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cerr << &ProgramErrorMessage[0] << std::endl;
    }

    return program_id;
}

