#include "Core.h"
#include <QtConcurrent/QtConcurrent>

Core *Core::instance = nullptr;

Core *Core::getInstance() {
    if (instance == nullptr) {
        instance = new Core();
    }
    return instance;
}

void Core::init(int port, std::string path) {
    Logger::startSection("Initializing core functions");
    this->port = port;

    if(path.substr(0,1) == ".") {
        this->path = QDir::currentPath().toStdString() + "/" + path;
    } else {
        this->path = path;
    }
    if(path.substr(path.length()-1, path.length()) != "/") {
        this->path.append("/");
    }

    Logger::log(this->path);

    Logger::startSection("Creating IOLoop");
    loop = new IOLoop();
    Logger::endSection();

    Logger::startSection("Creating server handler");
    new ServerHandler(port);
    Logger::endSection();

    Logger::startSection("Loading songs");
    QDir songsFolder(QString::fromStdString(path));
    songsFolder.setNameFilters(QStringList() << "*.mp3");
    QStringList songsFileList = songsFolder.entryList();
    for (auto song : songsFileList) {
        QString string;
        Logger::log("Adding song " + song.toStdString());
        songs.push_back(song.toStdString());
    }
    if(songs.empty()) {
        Logger::log("Could not load songs from path: " + this->path);
        exit(EXIT_FAILURE);
    }
    Logger::endSection();

    Logger::startSection("Initializing poll");
    poll = new Poll();
    startNewPoll();
    Logger::endSection();

    Logger::startSection("Initializing player");
    player = new Player();
    Logger::endSection();

    Logger::endSection();
}

void Core::ioLoopStart() {
    Logger::startSection("Starting IOLoop");
    loop->start();
    Logger::endSection();
}

void Core::start() {
    std::string winner = poll->getWinner();
    player->start(path, winner);
    Logger::log("The winner is: " + winner.substr(0, winner.length() - 4));
    startNewPoll();
    resetVotes();
    sendNotificationToAll();
}

void Core::addServerHandler(int fd, Handler *handler) {
    loop->addHandler(fd, handler, EPOLLIN);
}

void Core::addClient(int fd, sockaddr_in addr) {
    Logger::startSection("Core::addClient");
    Logger::log(inet_ntoa(addr.sin_addr));
    clients.insert(std::make_pair(fd, new ClientHandler(fd)));
    loop->addHandler(fd, (Handler *) clients[fd], EPOLLIN | EPOLLRDHUP | EPOLLHUP);
    Logger::endSection();
}


void Core::removeClient(int fd) {
    Logger::startSection("Core::removeClient");
    clients.erase(fd);
    loop->removeHandler(fd);
    Logger::endSection();
}

void Core::sendStatsToClient(ClientHandler *client, std::vector<std::pair<std::string, int>> stats) {
    int i = 0;
    for (auto stat : stats) {
        client->sendMessage(300 + i, stat.first + "::" + std::to_string(stat.second) + '\n');
        i++;
    }
}

void Core::sendStatsToAllClients() {
    for (auto client : clients) sendStatsToClient(client.second, poll->getStats());
}

void Core::sendNotificationToAll() {
    for (auto client : clients) client.second->sendMessage(100, "");
}

void Core::startNewPoll() {
    Logger::startSection("Creating new poll");
    poll->newPoll(songs);
    for (auto option : poll->getStats()) {
        Logger::log(option.first);
    }
    this->resetVotes();
    Logger::endSection();
}

void Core::vote(ClientHandler *client, int vote) {
    client->setVoted(true);
    poll->vote(vote);
    sendStatsToAllClients();
}

void Core::resetVotes() {
    for (auto client : clients) client.second->setVoted(false);
}

std::vector<std::pair<std::string, int> > Core::getPollStats() {
    return poll->getStats();
}

Player *Core::getPlayer() {
    return player;
}
