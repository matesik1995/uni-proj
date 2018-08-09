#include "player.h"
#include "logger.h"
#include "Core.h"

Player::Player(QObject *parent) : QObject(parent)
{
    mediaPlayer = new QMediaPlayer();
    timer = new QTimer(this);
    connect(timer, SIGNAL (timeout()), this, SLOT (update()));
}

void Player::start(std::string path, std::string name)
{
    mediaPlayer->setMedia(QUrl::fromLocalFile(QString::fromStdString(path+name)));
    mediaPlayer->play();
    this->title = name.substr(0,name.length()-4);
    this->total= mediaPlayer->duration();
    this->elapsed=0;
    timer->start(500);
}

std::string Player::getTitle()
{
    return title;
}

int Player::getElapsed()
{
    return elapsed;
}

int Player::getTotal()
{
    return total;
}

void Player::update()
{
    elapsed = mediaPlayer->position()/1000;
    total = mediaPlayer->duration()/1000;
    if(elapsed >= total) {
        timer->stop();
        Core::getInstance()->start();
    }
    Logger::log(std::to_string(elapsed) +"/"+std::to_string(total));
}
