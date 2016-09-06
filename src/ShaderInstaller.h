#pragma once

#include <boost/filesystem.hpp>

#include <GL/glew.h>

namespace fs = boost::filesystem;

class ShaderInstaller
{
public:
     GLuint installShaders(const fs::path& vertex_shader_file, const fs::path& fragment_shader_file);

private:
    GLint checkCompileStatus(GLuint shader_id) const;

};
