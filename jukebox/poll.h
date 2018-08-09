#ifndef POLL_H
#define POLL_H

#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

class Poll
{
    std::vector<std::pair<std::string, int>> options;

public:
    Poll() = default;
    void newPoll(std::vector<std::string> songs);
    void vote(int index);
    std::string getWinner();
    std::vector<std::pair<std::string, int>> getStats();
};

#endif // POLL_H
