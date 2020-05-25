#include "game.h"


Game::Game()
{
    m_scene = new QGraphicsScene(0,0,LONGUEUR_FENETRE,LARGEUR_FENETRE);
    setScene(m_scene);
}

void Game::start(){
    //création de la tête du serpent
    SnakeHead *snake_head = new SnakeHead();
    //ajout de la tête du serpent à la scène
    m_scene->addItem(snake_head);
    snake_head->setFocus();

}
