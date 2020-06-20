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
    setRect(1,1,LONGUEUR_TETE-2,LONGUEUR_TETE-2);
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
    m_snake_body.push_back(bloc1);
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

//variable globale pour aider à afficher le fruit après X périodes
//de sa déstruction
int aide_affichage_fruit = 0;
void SnakeHead::keyPressEvent(QKeyEvent *event)
{
    //Afin de corriger un bug où le fruit ne disparaît pas lorsqu'on
    //appuie sur une touche juste avant de manger le fruit
    //On teste alors s'il y a eu de collision au moment où on appuie
    //sur une touche
    bool aide_detection_collision = false;
    bool aide_detection_collision_go = false;
    if(verify_position() && m_direction != "NULL"){
        m_prev_pos = pos();
        if(event->key() == Qt::Key_Right){
            if(m_direction != "LEFT"){
                if(m_direction != "RIGHT"){
                    setPos(x() + LONGUEUR_TETE, y());
                    aide_detection_collision = collisionImplement(CYCLE_FRUIT);
                    moveBody(aide_detection_collision);
                    collideSnake();
                    m_direction = "RIGHT";
                    }
                }
            }

        else if(event->key() == Qt::Key_Left){
                if(m_direction != "RIGHT"){
                    if(m_direction != "LEFT"){
                        setPos(x() - LONGUEUR_TETE, y());
                        aide_detection_collision = collisionImplement(CYCLE_FRUIT);
                        moveBody(aide_detection_collision);
                        collideSnake();
                        m_direction = "LEFT";
                    }
            }
        }
        else if(event->key() == Qt::Key_Up){
                if(m_direction != "DOWN"){
                    if(m_direction != "UP"){
                        setPos(x(), y() - LONGUEUR_TETE);
                        aide_detection_collision = collisionImplement(CYCLE_FRUIT);
                        moveBody(aide_detection_collision);
                        collideSnake();
                        m_direction = "UP";
                    }
                }
            }
        else if(event->key() == Qt::Key_Down){
                if(m_direction != "UP"){
                   if(m_direction != "DOWN"){
                        setPos(x(), y() + LONGUEUR_TETE);
                        aide_detection_collision = collisionImplement(CYCLE_FRUIT);
                        moveBody(aide_detection_collision);
                        collideSnake();
                        m_direction = "DOWN";
                    }
                  }
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
    if(collision_detected){
        SnakeBody* snake_body = new SnakeBody();
        m_snake_body.push_back(snake_body);
        qDebug() <<"new Snake_body created, taille m_snake.body.size : " << m_snake_body.size();
    }
   //bouger le corps du serpent
   //de la dernière partie jusqu'à la première
    for (int i = m_snake_body.size()-1; i > 0; i--){
        m_snake_body.at(i)->setPos(m_snake_body[i-1]->pos());
    }
    //la partie du corps 0 a la position précédente de la tête
    m_snake_body.at(0)->setPos(m_prev_pos);
    //ajouter le dernier morceau à la scène s'il y a eu une collision
    if(collision_detected)
        game->getScene()->addItem(m_snake_body.at(n));


}

int SnakeHead::getX(){
    return this->x();
}

int SnakeHead::getY(){
    return this->y();
}

bool SnakeHead::collideSnake(){
    QList<QGraphicsItem*> colliding_items_GO = collidingItems();
    bool collision_detected_gameOver = false;
    for(int i =0; i <colliding_items_GO.size() ; i++){
        if(typeid(*colliding_items_GO[i]) == typeid(SnakeBody) ){
            //qDebug() << "Touché mais pas dedans";
            GameOver();
            collision_detected_gameOver = true;
            break;
        }
    }
    return collision_detected_gameOver;
}


bool SnakeHead::collideFruit(){
   QList<QGraphicsItem*> colliding_items = collidingItems();
   bool collision_detected = false;
   for(int i =0; i <colliding_items.size() ; i++){
    if(typeid(*(colliding_items.at(i))) == typeid(Fruit) ){
        //supprimer le fruit
        game->getScene()->removeItem(colliding_items.at(i));
        game->score->setScore(game->score->getScore()+1);

        //supprimer le fruit de la mémoire
        delete colliding_items.at(i);
        qDebug() << "collideFruit";
        collision_detected = true;
        break;
        }
    }
   //s'il n'y a pas eu de collisions
   return collision_detected;
}




//afficher le fruit après "cycle" périodes
bool SnakeHead::collisionImplement(int cycle){
    bool collision_detected_local = collideFruit();
    if(collision_detected_local){
        //initialiser la variable aide_affichage_fruit pour afficher le fruit
        aide_affichage_fruit = 1;
    }
    //incrémenter la valeur de la variable
    if(aide_affichage_fruit >0)
        aide_affichage_fruit ++;
    //afficher un nouveau fruit après "cycle" périodes
    if(aide_affichage_fruit == cycle){
        Fruit* fruit = new Fruit();
        aide_affichage_fruit = 0;
    }
    return collision_detected_local;
}

//mouvement automatique
void SnakeHead::move(){
    //faire bouger la tête suivant sa direction actuelle automatiquement
    //si le serpent n'est pas en pause
    bool collision_detected = false;
    bool collision_detected_go = false;
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

        /*if(collideFruit()){
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
        }*/
        collision_detected = collisionImplement(CYCLE_FRUIT);
        collideSnake();
        moveBody(collision_detected);
        collision_detected = false;
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

void SnakeHead::GameOver()
{
    m_direction = "NULL";
    game->GameOver();
}
