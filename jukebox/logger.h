#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

class Logger
{
    static int level;
public:
    Logger() = default;

    static void log(std::string message);
    static void startSection(std::string message);
    static void endSection();
    static void error(std::string message);
};

#endif // LOGGER_H
