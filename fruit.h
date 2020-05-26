#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
//Pour afficher une image pour signifier le fruit
class Fruit: public QGraphicsEllipseItem
{
public:
    Fruit();
    //retourner les coordonnées du fruit
    int getX();
    int getY();
private:
       int score;
};


