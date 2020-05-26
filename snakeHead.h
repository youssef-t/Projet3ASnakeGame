#pragma once
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QBrush>
#include "constants.h"
#include "snakeBody.h"
#include <QList>
#include <QPointF>
#include <QString>
class SnakeHead : public QGraphicsRectItem
{
public:
    //constructeur pour créer la tête du serpent
    SnakeHead();
    //méthode pour controler la tête
    void keyPressEvent(QKeyEvent* event);
    //bouger les blocs qui composent le corps
    void moveBody();
    //augmenter la taille du serpent
    void elongateBody();
    //retourner les coordonnées de la tête
    int getX();
    int getY();



private:
    //int m_length_head;
    QList<SnakeBody*> m_snake_body;
    //le premier bloc créé après la tête et qui compose le corps au début
    QPointF m_prev_pos;
    QString m_direction;

};

