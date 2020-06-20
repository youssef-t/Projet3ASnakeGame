#include "game.h"
#include "snakeHead.h"
#include <QDebug>


Game::Game()
{   //définir la taille de la fenêtre
    setFixedSize(LONGUEUR_FENETRE,LARGEUR_FENETRE);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_scene = new QGraphicsScene(0,0,LONGUEUR_FENETRE,LARGEUR_FENETRE);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor::fromRgb(249, 204, 23));
    m_scene->setBackgroundBrush(brush);
    setScene(m_scene);
    score = new Score();
    m_scene->addItem(score);
}

void Game::displayMainMenu(QString title,QString play)
{
  //Create the title
    titleText = new QGraphicsTextItem(title);
    QFont titleFont("arial" , 50);
    titleText->setFont( titleFont);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 150;
    titleText->setPos(xPos,yPos);
    m_scene->addItem(titleText);

    //create Button
    Button * playButton = new Button(play,titleText);
    int pxPos = -20 ;
    int pyPos = 160;
    playButton->setPos(pxPos,pyPos);

    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    m_scene->addItem(playButton);


    //Create Quit Button
    Button * quitButton = new Button("Quit",titleText);
    int qxPos = -20;
    int qyPos = 230;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));
    m_scene->addItem(quitButton);

}

void Game::start(){
    //Création de la tête du serpent
    //Lors de l'appel du constructeur
    //l'objet est mis sur la "scène"
    m_scene->removeItem(titleText);
    SnakeHead *snake_head = new SnakeHead();
    score->setVisible(true);
    score->setScore(0);

    //snake_head->setFocus();
    Fruit* fruit = new Fruit();
    //m_scene->addItem(fruit);

    // elongate if collides with Fruit
      // if (snake_head->getX() == fruit->getX() && snake_head->getY() == fruit->getY()){
        //  snake_head->elongateBody();
        //}


}

QGraphicsScene* Game::getScene() const{
    return m_scene;
}

void Game::GameOver()
{
    titleTextGameOver = new QGraphicsTextItem("Game Over");
    QFont titleFont("arial" , 50);
    titleTextGameOver->setFont( titleFont);
    int xPos = width()/2 - titleTextGameOver->boundingRect().width()/2;
    int yPos = 150;
    titleTextGameOver->setPos(xPos,yPos);
    m_scene->addItem(titleTextGameOver);
    QBrush gameover;
    gameover.setStyle(Qt::SolidPattern);
    gameover.setColor(Qt::darkRed);
    m_scene->setBackgroundBrush(gameover);


    Button * quitButton = new Button("Quitter",titleTextGameOver);
    int qxPos = 30;
    int qyPos = 230;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));
    m_scene->addItem(quitButton);
}
