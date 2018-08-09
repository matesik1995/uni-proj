#include "IOLoop.h"

IOLoop::IOLoop() {
    epfd = epoll_create1(0);
    if (epfd < 0) {
        Logger::error("Failed to create epoll");
        exit(EXIT_FAILURE);
    }
}

void IOLoop::addHandler(int fd, Handler *handler, unsigned int events) {
    Logger::startSection("IOLoop::addHandler");
    handlers.insert(std::make_pair(fd, handler));
    epoll_event ev{};
    ev.data.fd = fd;
    ev.events = events;

    if(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) < 0) {
        Logger::error("Failed to register handler");
    }
    Logger::endSection();
}

void IOLoop::removeHandler(int fd) {
    Logger::startSection("IOLoop::removeHandler");
    if(epoll_ctl(epfd, EPOLL_CTL_DEL, fd, nullptr) < 0) {
        Logger::error("Failed to deregister handler");
    }
    handlers.erase(fd);
    close(fd);
    Logger::endSection();
}

void IOLoop::start() {
    int nfds, n;
    for(;;) {
        nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            Logger::error("epoll_wait");
            exit(EXIT_FAILURE);
        }
        Logger::startSection("Processing " + std::to_string(nfds) + " events: ");
        for (n = 0; n < nfds; ++n) {
            int fd = this->events[n].data.fd;
            Handler *h = handlers[fd];
            h->handle(this->events[n]);
        }
        Logger::endSection();
    }
}
