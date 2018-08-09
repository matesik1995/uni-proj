#include "ServerHandler.h"
#include "Core.h"

ServerHandler::ServerHandler(uint16_t port) {
    if ((fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        Logger::error("Failed to create server socket");
        exit(EXIT_FAILURE);
    }

    int enable = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        Logger::error("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr{};
//    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        Logger::error("Failed to bind server socket");
        exit(EXIT_FAILURE);
    }

    if (listen(fd, BACKLOG_SIZE) < 0) {
        Logger::error("Failed to listen on server socket");
        exit(EXIT_FAILURE);
    }

    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);

    Core::getInstance()->addServerHandler(fd, this);
}

int ServerHandler::handle(epoll_event e) {
    Logger::startSection("ServerHandler::handle");
    if(e.events & EPOLLIN) {
        sockaddr_in client_addr{};
        socklen_t ca_len = sizeof(client_addr);

        int client = accept(fd, (struct sockaddr *) &client_addr, &ca_len);

        if(client < 0) {
            Logger::error("Error accepting connection");
            return -1;
        }
        Core::getInstance()->addClient(client, client_addr);
        Logger::log("Client connected: " + std::string(inet_ntoa(client_addr.sin_addr)));
    } else {
        Logger::log("Unknown event " + std::to_string(e.events));
    }
    Logger::endSection();
    return 0;
}
