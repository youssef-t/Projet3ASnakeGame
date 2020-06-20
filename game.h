#pragma once
#include "snakeHead.h"
#include "constants.h"
#include "fruit.h"
#include "score.h"
class Game : public QGraphicsView
{
public:
    Game();
    Score *score;
    void start();
    QGraphicsScene* getScene() const;
    void gameOver();
private:
    QGraphicsScene* m_scene;
    int m_score;
};
