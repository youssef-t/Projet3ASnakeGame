#include <QApplication>
#include "fruit.h"
#include "game.h"
#include "snakeBody.h"
#include "snakeHead.h"

//variables globales
Game* game;
Fruit* fruit;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    game->start();

    return a.exec();
}
