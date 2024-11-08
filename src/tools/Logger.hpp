#pragma once

#include <string>

namespace gui
{
namespace tools
{
class Logger
{
public:
    Logger(const std::string name, const std::string& outputFile = "");
    void info(const char* format, ...) const;
    void debug(const char* format, ...) const;
    void warn(const char* format, ...) const;
    void error(const char* format, ...) const;
private:
    std::string name_;
    std::string outputFile_;
    FILE* outFileHandle_{nullptr};
};
} // namespace tools
} // namespace gui