#include "Logger.hpp"

#include <stdio.h>
#include <cstdarg>

namespace gui
{
namespace tools
{
Logger::Logger(const std::string name, const std::string& outputFile)
    : name_{name}
    , outputFile_ {outputFile}
{}

void Logger::info(const char* format, ...) const
{
    va_list vList;
    va_start(vList, format);
    fprintf(stdout, "[INF][%s] ", name_.c_str());
    vfprintf(stdout, format, vList);
    fprintf(stdout, "\n");
    va_end(vList);
}

void Logger::debug(const char* format, ...) const
{
    va_list vList;
    va_start(vList, format);
    fprintf(stdout, "[DBG][%s] ", name_.c_str());
    vfprintf(stdout, format, vList);
    fprintf(stdout, "\n");
    va_end(vList);
}

void Logger::warn(const char* format, ...) const
{
    va_list vList;
    va_start(vList, format);
    fprintf(stdout, "[WRN][%s] ", name_.c_str());
    vfprintf(stdout, format, vList);
    fprintf(stdout, "\n");
    va_end(vList);
}

void Logger::error(const char* format, ...) const
{
    va_list vList;
    va_start(vList, format);
    fprintf(stderr, "[ERR][%s] ", name_.c_str());
    vfprintf(stderr, format, vList);
    fprintf(stderr, "\n");
    va_end(vList);
}

} // namespace tools
} // namespace gui