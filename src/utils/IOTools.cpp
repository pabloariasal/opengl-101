#include "IOTools.h"

#include <fstream>
#include <sstream>

std::string IOTools::readTextFile(const fs::path &file_name)
{
    std::ifstream file(file_name.string());
    std::stringstream ss;

    if(file.is_open())
    {
        ss << file.rdbuf(); // read entire file
    }
    else
    {
        std::cerr << "Could not open file " << file_name.string() << std::endl;
    }

    file.close();

    return ss.str();
}
