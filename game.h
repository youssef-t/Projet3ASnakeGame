#pragma once
#include "snakeHead.h"
#include "constants.h"
class Game : public QGraphicsView
{
public:
    Game();
    void start();

private:
    QGraphicsScene* m_scene;
};
