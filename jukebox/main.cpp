#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>
#include "Core.h"
#include <string>

int main(int argc, char *argv[])
{
    int one = 1;
    int port = 12333;
    std::string path = std::string("./songs/");
    QCoreApplication a(one, argv);
    if (argc >= 2) {
        port = atoi(argv[1]);
    }
    if (argc >= 3) {
        path = argv[2];
    }
    Core::getInstance()->init(port, path);
    QtConcurrent::run(Core::getInstance(), &Core::ioLoopStart);
    Core::getInstance()->start();
    a.exec();
    return 0;
}
