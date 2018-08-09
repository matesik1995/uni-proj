#include "messageparser.h"
#include "Core.h"
#include <string>
#include "logger.h"

void MessageParser::parse(ClientHandler *client, char *msg)
{
    int code = atoi(msg);
    Logger::log(std::to_string(code));
    switch(code/100) {
        case 1:
            if (code%10==1) client->sendMessage(101, Core::getInstance()->getPlayer()->getTitle());
            if (code%10==2) client->sendMessage(102, std::to_string(Core::getInstance()->getPlayer()->getElapsed()));
            if (code%10==3) client->sendMessage(103, std::to_string(Core::getInstance()->getPlayer()->getTotal()));
            break;
        case 2:
            if (code%10 < 8 && !client->getVoted()) {
                Core::getInstance()->vote(client, code%10);
            }
            break;
        case 3:
            Core::getInstance()->sendStatsToClient(client, Core::getInstance()->getPollStats());
            break;
        default:break;
    }
}
