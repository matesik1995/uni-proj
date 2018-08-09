#include "logger.h"

int Logger::level = 1;

void Logger::log(std::string message)
{
    std::string prefix;
    prefix.append(level, '*');
    std::cout << prefix << " " << message << std::endl;
}

void Logger::startSection(std::string message)
{
    std::string prefix;
    prefix.append(level, '*');
    std::cout << prefix << " " << message << std::endl;
    level++;
}

void Logger::endSection()
{
    level--;
    std::string prefix;
    prefix.append(level, '*');
    std::cout << prefix << " done"<< std::endl;
}

void Logger::error(std::string message)
{
    std::string prefix;
    prefix.append(level, '*');
    std::cout << prefix << message << std::endl;
    perror("perror: ");
}
