#pragma once

#include <cstdint>
#include <string>

namespace gui
{
namespace tools
{
class Logger
{
public:
    enum Level : uint8_t
    {
        ERROR   = (1 << 0),
        INFO    = (1 << 1),
        WARNING = (1 << 2),
        DEBUG   = (1 << 3),
        ALL     = ERROR | INFO | WARNING | DEBUG
    };
public:
    Logger(const std::string name, const std::string& outputFile = "");
    void infoLine(const char* format, ...) const;
    void info(const char* format, ...) const;
    void debug(const char* format, ...) const;
    void warn(const char* format, ...) const;
    void error(const char* format, ...) const;

    static void setLevels(const uint8_t level);
    static void unsetLevels(const uint8_t level);
private:
    std::string name_;
    std::string outputFile_;
    FILE* outFileHandle_{nullptr};

    static uint8_t allowedLevels;
};
} // namespace tools
} // namespace gui