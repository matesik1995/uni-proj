//
// Created by matesik on 20.01.18.
//

#ifndef HANDLER_H
#define HANDLER_H


#include <sys/epoll.h>

class Handler {
public:
    virtual int handle(epoll_event) = 0;
};


#endif //HANDLER_H
