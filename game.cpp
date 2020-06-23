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

void Game::displayMainMenu(QString title,QString play, bool rejouer)
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
    int pxPos = 0 ;
    if(title == "Game Over")
        pxPos = 75;
    int pyPos = 160;
    playButton->setPos(pxPos,pyPos);
    if(!rejouer)
       connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
   else{
       connect(playButton, SIGNAL(clicked()), this, SLOT(playAgain()));
    }
    m_scene->addItem(playButton);


    //Create Quit Button
    Button * quitButton = new Button("Quit",titleText);
    int qxPos = pxPos;
    int qyPos = 230;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));
    m_scene->addItem(quitButton);

}

//si l'utilisateur souhaite rejouer
void Game::playAgain()
{   qDebug()<< "In play again";
    QList<QGraphicsItem*> all = items();
    for (int i = 0; i < all.size(); i++){
            QGraphicsItem *gi = all[i];
            m_scene->removeItem(gi);
            if(typeid (*gi) != typeid (Score))
                delete gi; // warning at this line
            qDebug()<<"removed "<< i ;
        }
    //ajout du serpent
    SnakeHead* snake_head = new SnakeHead();
    qDebug() << "Snake Head created in playagain()";
    //réinitialiser le score
    score->setScore(0);
    m_scene->addItem(score);
    //ajout du fruit
    Fruit* fruit = new Fruit();
    //changer la couleur du background
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor::fromRgb(249, 204, 23));
    m_scene->setBackgroundBrush(brush);

}

void Game::start(){
    //Création de la tête du serpent
    //Lors de l'appel du constructeur
    //l'objet est mis sur la "scène"
    m_scene->removeItem(titleText);
    SnakeHead* snake_head = new SnakeHead();
    score->setVisible(true);
    score->setScore(0);

    //snake_head->setFocus();
    Fruit* fruit = new Fruit();
    //m_scene->addItem(fruit);

}

QGraphicsScene* Game::getScene() const{
    return m_scene;
}

void Game::GameOver()
{
    QBrush gameover;
    gameover.setStyle(Qt::SolidPattern);
    gameover.setColor(Qt::darkRed);
    m_scene->setBackgroundBrush(gameover);
    displayMainMenu("Game Over", "Rejouer", true);
}
