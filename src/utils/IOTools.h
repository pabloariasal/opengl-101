#pragma once

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class IOTools
{
public:
    static std::string readTextFile(const fs::path& file_name);

};
