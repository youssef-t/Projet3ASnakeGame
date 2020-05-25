#include <QApplication>
#include "fruit.h"
#include "game.h"
#include "snakeBody.h"
#include "snakeHead.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game game;
    game.show();
    game.start();

    return a.exec();
}
