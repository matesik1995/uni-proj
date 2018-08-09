#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <QObject>
#include <QTimer>
#include <QMediaPlayer>

class Player : public QObject {
    Q_OBJECT

public:
    explicit Player(QObject *parent = 0);
    void start(std::string path, std::string name);
    std::string getTitle();
    int getElapsed();
    int getTotal();

public slots:
    void update();

private:
    QMediaPlayer *mediaPlayer;
    QTimer *timer;
    std::string title;
    int elapsed;
    int total;
};

#endif // PLAYER_H
