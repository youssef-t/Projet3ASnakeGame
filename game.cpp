#include "game.h"


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
    m_score = 0;
}

void Game::start(){
    //Création de la tête du serpent
    //Lors de l'appel du constructeur
    //l'objet est mis sur la "scène"
    SnakeHead *snake_head = new SnakeHead();

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

void Game::gameOver(){

    //m_scene->removeItem(snake_head);

}
