#pragma once
#include "snakeHead.h"
#include "constants.h"
#include "fruit.h"
class Game : public QGraphicsView
{
public:
    Game();
    void start();
    QGraphicsScene* getScene() const;
    void gameOver();
private:
    QGraphicsScene* m_scene;
};
