#pragma once
#include "snakeHead.h"
#include "constants.h"
#include "fruit.h"
#include "score.h"
#include "button.h"
#include <QPushButton>
class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    Score *score;
    QGraphicsScene* getScene() const;
    void GameOver();
    void displayMainMenu(QString title, QString play, bool rejouer = false);

private:
    QGraphicsTextItem *titleText;
    QGraphicsTextItem *titleTextGameOver;
    QGraphicsScene* m_scene;
    int m_score;

public slots:
    void start();
    void playAgain();
};
