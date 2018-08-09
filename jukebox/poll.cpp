#include "poll.h"

void Poll::newPoll(std::vector<std::string> songs)
{
    options.clear();
    srand (time(nullptr));
    while(options.size()<8) {
        options.emplace_back(songs.at(rand() % songs.size()), 0);
    }
}

void Poll::vote(int index)
{
    options.at(index).second++;
}

std::string Poll::getWinner()
{
    srand (time(nullptr));
    int max=0;
    std::vector<std::string> winners;
    for (auto &option : options) {
        if(option.second>max) {
            max= option.second;
            winners.clear();
            winners.push_back(option.first);
        } else if (option.second==max) {
            winners.push_back(option.first);
        }
    }
    if (winners.size() == 1) {
        return winners.at(0);
    } else {
        return winners.at(rand() % winners.size());
    }
}

std::vector<std::pair<std::string, int>> Poll::getStats()
{
    return options;
}
