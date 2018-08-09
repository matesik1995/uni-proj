#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
#include <iostream>
#include "QDir"

#include "poll.h"
#include "player.h"
#include "logger.h"
#include "ServerHandler.h"
#include "ClientHandler.h"
#include "IOLoop.h"

class Core {
    static Core *instance;
    IOLoop *loop;
    Player *player;
    Poll *poll;
    std::vector<std::string> songs;
    std::map<int, ClientHandler *> clients;

    Core() = default;

    int port;
    std::string path;

public:
    static Core *getInstance();

    void init(int port, std::string path);

    void ioLoopStart();

    void start();

    void addServerHandler(int fd, Handler *handler);

    void addClient(int fd, sockaddr_in addr);

    void removeClient(int fd);

    void sendStatsToClient(ClientHandler *client, std::vector<std::pair<std::string, int>>);

    void sendStatsToAllClients();

    void sendNotificationToAll();

    void startNewPoll();

    void vote(ClientHandler *client, int vote);

    void resetVotes();

    std::vector<std::pair<std::string, int>> getPollStats();

    Player *getPlayer();
};


#endif //CORE_H
