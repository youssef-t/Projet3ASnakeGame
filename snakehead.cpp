#include "snakeHead.h"
#include "game.h"
#include <QTimer>
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
    /*SnakeBody* bloc2 = new SnakeBody();
    bloc2->setPos(POS_INIT_TETE_X - 2*LONGUEUR_TETE, POS_INIT_TETE_Y);
    game->getScene()->addItem(bloc2);
    m_snake_body.prepend(bloc2);*/

    //initialiser m_last_key_pressed
    m_direction = "RIGHT";

    //bouger la tête périodiquement
    m_periode = 300;
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    //vitesse du mouvement
    timer->start(m_periode);
}


void SnakeHead::keyPressEvent(QKeyEvent *event)
{
    if(verify_position()){
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
    }
    //faire une pause
    else if(event->key() == Qt::Key_Space){
        if(m_direction == "NULL"){
            m_direction = m_direction_before_space;
        }
        else {
            m_direction_before_space = m_direction;
            m_direction = "NULL";
        }
    }

}

void SnakeHead::moveBody(){
    int n = m_snake_body.size();
    // faire bouger chaque bloc à l'ancien emplacement du bloc qui le suit
    m_snake_body.first()->setPos(m_prev_pos);
    for (auto i = 0; i < n -1; i++){
        m_snake_body[i+1]->setPos(m_snake_body[i]->pos());
    }
    /* QPointF prev_pos;
     prev_pos = m_snake_body.first()->pos();
     m_snake_body.first()->setPos(m_prev_pos);
     m_prev_pos = prev_pos;
     //m_prev_pos = m_snake_body.first()->pos();
     for (auto i = 0; i < n -1; i++){
         prev_pos = m_snake_body.first
         m_snake_body[i+1]->setPos();
         m_snake_body[i]->pos(m_prev_pos);
     }
 */

}

void SnakeHead::elongateBody()
{
    //ajouter un nouveau bloc
    SnakeBody* bloc = new SnakeBody();
    m_snake_body.prepend(bloc);

    // Ajouter le bloc à la scène
    //if (m_direction == "")
    bloc->setPos(-200,-200);
    game->getScene()->addItem(bloc);
}

int SnakeHead::getX(){
    return this->x();
}

int SnakeHead::getY(){
    return this->y();
}

//mouvement automatique
void SnakeHead::move(){
    //faire bouger la tête suivant sa direction actuelle automatiquement
    correction_position();
    m_prev_pos = pos();
    if(m_direction == "LEFT")
        setX(this->x() - LONGUEUR_TETE);
    else if(m_direction == "RIGHT")
        setX(this->x() + LONGUEUR_TETE);
    else if(m_direction == "UP")
        setY(this->y() - LONGUEUR_TETE);
    else if(m_direction == "DOWN")
        setY(this->y() + LONGUEUR_TETE);
    moveBody();

}

void SnakeHead::correction_position(){
    if(x() < 0)
        setX(LONGUEUR_FENETRE);
    else if (x() > LONGUEUR_FENETRE)
        setX(0);
    else if (y() < 0)
        setY(LARGEUR_FENETRE);
    else if( y() > LARGEUR_FENETRE)
        setY(0);
}

bool SnakeHead::verify_position()
{
    if(x() < 0)
        return false;
    else if(x() > LONGUEUR_FENETRE)
        return false;
    else if(y() < 0)
        return false;
    else if(y() > LARGEUR_FENETRE)
        return false;
    return true;
}


