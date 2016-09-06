#include "ShaderInstaller.h"

#include <string.h>
#include "utils/IOTools.h"

GLuint ShaderInstaller::installShaders(const fs::path& vertex_shader_file, const fs::path& fragment_shader_file)
{

    //Read shaders from text file
    std::string vertex_source = IOTools::readTextFile(vertex_shader_file);
    std::string fragment_source = IOTools::readTextFile(fragment_shader_file);

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
        std::cerr << "Problem appeared while compiling shaders. Exiting program..." << std::endl;
        exit(1);
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

    if ( InfoLogLength > 0 )
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(program_id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    return program_id;
}

GLint ShaderInstaller::checkCompileStatus(GLuint shader_id) const
{
    GLint result = GL_FALSE;
    int InfoLogLength;

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(shader_id, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    return result;

}
