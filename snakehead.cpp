#include "snakeHead.h"
#include "game.h"
#include <QTimer>
#include <QDebug>
#include "fruit.h"
/*SnakeHead est une classe fille de QGraphicsRectItem
  Alors on peut utiliser les méthodes que contient cette classe*/

extern Game* game;
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
    m_periode = SPEED_SNAKE;
    QTimer* timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    //vitesse du mouvement
    timer->start(m_periode);


}

//variable globale pour aider à afficher le fruit après 5 périodes
//de sa déstruction
int aide_affichage_fruit = 0;
void SnakeHead::keyPressEvent(QKeyEvent *event)
{
    if(verify_position()){
        if(event->key() == Qt::Key_Right){
            if(m_direction != "LEFT"){
                if(m_direction != "RIGHT"){
                    m_prev_pos = pos();
                    setPos(x() + LONGUEUR_TETE, y());
                    moveBody();
                    m_direction = "RIGHT";
                    }
                }
            }

        else if(event->key() == Qt::Key_Left){
                if(m_direction != "RIGHT"){
                    if(m_direction != "LEFT"){
                        m_prev_pos = pos();
                        setPos(x() - LONGUEUR_TETE, y());
                        moveBody();
                        m_direction = "LEFT";
                    }
            }
        }
        else if(event->key() == Qt::Key_Up){
                if(m_direction != "DOWN"){
                    if(m_direction != "UP"){
                        m_prev_pos = pos();
                        setPos(x(), y() - LONGUEUR_TETE);
                        moveBody();
                        m_direction = "UP";
                    }
                }
            }
        else if(event->key() == Qt::Key_Down){
                if(m_direction != "UP"){
                   if(m_direction != "DOWN"){
                        m_prev_pos = pos();
                        setPos(x(), y() + LONGUEUR_TETE);
                        moveBody();
                        m_direction = "DOWN";
                    }
                  }
            }
        //Afin de corriger un bug où le fruit ne disparaît pas lorsqu'on
        //appuie sur une touche juste avant de manger le fruit
        if(collideFruit()){
            //initialiser la variable aide_affichage_fruit pour afficher le fruit
            aide_affichage_fruit = 1;
        }
        //incrémenter la valeur de la variable
        if(aide_affichage_fruit >0)
            aide_affichage_fruit ++;
        //afficher un nouveau fruit après 7 périodes
        if(aide_affichage_fruit == 8){
            Fruit* fruit = new Fruit();
            aide_affichage_fruit = 0;
        }
    }
    //faire une pause
    if(event->key() == Qt::Key_Space){
        //qDebug() << "Space pressed";
        if(m_direction == "NULL"){
            m_direction = m_direction_before_space;
        }
        else {
            m_direction_before_space = m_direction;
            m_direction = "NULL";
        }
    }


}

void SnakeHead::moveBody(bool collision_detected){
    int n = m_snake_body.size();
    // faire bouger chaque bloc à l'ancien emplacement du bloc qui le suit
    m_snake_body.first()->setPos(m_prev_pos);
    if(collision_detected){
        SnakeBody* snake_body = new SnakeBody();
        m_snake_body.append(snake_body);
        qDebug() <<"new Snake_body created, taille m_snake.body.size : " << m_snake_body.size();
    }
   //bouger le corps du serpent
    for (int i = m_snake_body.size()-1; i > 0; i--){
        m_snake_body.at(i)->setPos(m_snake_body[i-1]->pos());
    }
    //ajouter le dernier morceau à la scène s'il y a eu une collision
    if(collision_detected)
        game->getScene()->addItem(m_snake_body.at(n));

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
/*
void SnakeHead::elongateBody()
{
    //ajouter un nouveau bloc
    SnakeBody* bloc = new SnakeBody();
    m_snake_body.prepend(bloc);

    // Ajouter le bloc à la scène
    //if (m_direction == "")
    bloc->setPos(200,200);
    game->getScene()->addItem(bloc);
}*/

int SnakeHead::getX(){
    return this->x();
}

int SnakeHead::getY(){
    return this->y();
}

bool SnakeHead::collideFruit(){
   QList<QGraphicsItem*> colliding_items = collidingItems();
   for(int i =0; i <colliding_items.size() ; i++){
    if(typeid(*(colliding_items.at(i))) == typeid(Fruit) ){
        //supprimer le fruit
        game->getScene()->removeItem(colliding_items.at(i));

        //supprimer le fruit de la mémoire
        delete colliding_items.at(i);
        return true;
        }
    }
   //s'il n'y a pas eu de collisions
   return false;
}


//mouvement automatique
void SnakeHead::move(){
    //faire bouger la tête suivant sa direction actuelle automatiquement
    //si le serpent n'est pas en pause
    bool collision_detected = false;
    if(m_direction != "NULL"){
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

        if(collideFruit()){
            //initialiser la variable aide_affichage_fruit pour afficher le fruit
            qDebug()<<"Collision détectée";
            collision_detected = true;
            aide_affichage_fruit = 1;
           // this->elongateBody();
        }
        //incrémenter la valeur de la variable
        if(aide_affichage_fruit >0)
            aide_affichage_fruit ++;
        //afficher un nouveau fruit après 7 périodes
        if(aide_affichage_fruit == 8){
            Fruit* fruit = new Fruit();
            aide_affichage_fruit = 0;
        }
        moveBody(collision_detected);
    }
}

void SnakeHead::correction_position(){
    if(x() < 0)
        setX(LONGUEUR_FENETRE);
    else if (x() > LONGUEUR_FENETRE)
        setX(0 - LONGUEUR_TETE); //pour que la tête apparaisse à droite de la fenêtre
    else if (y() < 0)
        setY(LARGEUR_FENETRE);
    else if( y() > LARGEUR_FENETRE)
        setY(0 - LONGUEUR_TETE); //pour que la tête apparaisse en haut de la fenêtre
}

bool SnakeHead::verify_position()
{
    if(x() < 0)
        return false;
    else if(x() > LONGUEUR_FENETRE - LONGUEUR_TETE)
        return false;
    else if(y() < 0)
        return false;
    else if(y() > LARGEUR_FENETRE - LONGUEUR_TETE)
        return false;
    return true;
}


