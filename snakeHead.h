#pragma once
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include "constants.h"

class SnakeHead : public QGraphicsRectItem
{
public:
    SnakeHead();
    //méthode pour controler la tête
    void keyPressEvent(QKeyEvent* event);

private:
    int m_length_head;
};

