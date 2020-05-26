#include "fruit.h"
#include "game.h"
#include <QBrush>

extern Game* game;
Fruit::Fruit()
{
    setRect(0,0,40,40);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
    setPos(120,120);
    game->getScene()->addItem(this);

    score = 1;
}

int Fruit::getX(){
    return this->getX();
}
int Fruit::getY(){
    return this->getY();
}
