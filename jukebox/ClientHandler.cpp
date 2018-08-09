#include "ClientHandler.h"
#include "Core.h"
#include "messageparser.h"

ClientHandler::ClientHandler(int fd) {
    this->fd = fd;
    this->voted = false;
}

int ClientHandler::handle(epoll_event e) {
    Logger::startSection("ClientHandler::handle");
    if (e.events & EPOLLRDHUP || e.events & EPOLLHUP) {
        Core::getInstance()->removeClient(fd);
    } else if (e.events & EPOLLIN) {
        if ((received = recv(fd, buffer, BUFFER_SIZE-1, 0)) <= 0) {
            Logger::error("Error reading from socket");
        } else if (received > 0) {
            buffer[received] = 0;
            MessageParser::parse(this, buffer);
        }
    }
    Logger::endSection();
    return 0;
}

void ClientHandler::sendMessage(int code, std::string msg) {
    std::string header;
    char temp[16];
    sprintf(temp, "%04d", code);
    header.append(std::string(temp));
    header.append("::");
    sprintf(temp, "%04d", static_cast<int>(msg.length()));
    header.append(std::string(temp));

    if (header.length() != send(fd, header.c_str(), header.length(), 0)) {
        Logger::error("error sending header: " + header);
    };
    if (msg.length() != send(fd, msg.c_str(), msg.length(), 0)) {
        Logger::error("error sending message: " + msg);
    }
}

void ClientHandler::setVoted(bool voted) {
    this->voted = voted;
}

bool ClientHandler::getVoted() {
    return voted;
}
