#include "snakeHead.h"
#include "game.h"
/*SnakeHead est une classe fille de QGraphicsRectItem
  Alors on peut utiliser les méthodes que contient cette classe*/

extern Game* game;
extern Fruit* fruit;
SnakeHead::SnakeHead()
{
    setRect(0,0,LONGUEUR_TETE,LONGUEUR_TETE);
    //Définir la couleur de la tête et sa texture
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor::fromRgb(255, 215, 13));
    setBrush(brush);
    //Définir la position initial de la tête du serpent
    setPos(POS_INIT_TETE_X, POS_INIT_TETE_Y);
    //rendre la tête "focussable" afin de pouvoir la contrôler à l'aide du clavier
    setFlag(QGraphicsItem::ItemIsFocusable);
    //ajout de la tête dans game
    this->setFocus();
    game->getScene()->addItem(this);

    //création du corps du serpent
    SnakeBody* bloc1 = new SnakeBody();
    bloc1->setPos(POS_INIT_TETE_X - LONGUEUR_TETE, POS_INIT_TETE_Y);
    game->getScene()->addItem(bloc1);
    m_snake_body.prepend(bloc1);

    //initialiser m_last_key_pressed
    m_direction = "null";
}


void SnakeHead::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right){
        if(m_direction != "LEFT"){
            m_prev_pos = pos();
            setPos(x() + LONGUEUR_TETE, y());
            moveBody();
            m_direction = "RIGHT";
       }
     }

    else if(event->key() == Qt::Key_Left){
            if(m_direction != "RIGHT"){
                m_prev_pos = pos();
                setPos(x() - LONGUEUR_TETE, y());
                moveBody();
                m_direction = "LEFT";
            }
    }
    else if(event->key() == Qt::Key_Up){
            if(m_direction != "DOWN"){
                m_prev_pos = pos();
                setPos(x(), y() - LONGUEUR_TETE);
                moveBody();
                m_direction = "UP";
            }
    }
    else if(event->key() == Qt::Key_Down){
            if(m_direction != "UP"){
               m_prev_pos = pos();
               setPos(x(), y() + LONGUEUR_TETE);
               moveBody();
               m_direction = "DOWN";
            }
    }

    // elongate if collides with Fruit
    //   if (getX() == fruit->getX() || getY() == fruit->getY()){
      //    elongateBody();
       //   }


}

void SnakeHead::moveBody(){
    int n = m_snake_body.size()-1;
    for (auto i = 0; i < n; ++i){
        m_snake_body[i]->setPos(m_snake_body[i+1]->pos());
    }

    // faire bouger chaque bloc à l'ancien emplacement du bloc qui le suit
    m_snake_body.last()->setPos(m_prev_pos);
}

void SnakeHead::elongateBody()
{
    //ajouter un nouveau bloc
    SnakeBody* bloc = new SnakeBody();
    m_snake_body.prepend(bloc);

    // properly position the body
    bloc->setPos(-200,-200); // TODO
    game->getScene()->addItem(bloc);
}

int SnakeHead::getX(){
    return this->getX();
}

int SnakeHead::getY(){
    return this->getY();
}
