#include "fruit.h"
#include "game.h"
#include <QBrush>
#include <math.h>
#include <QDebug>

extern Game* game;
Fruit::Fruit()
{   //génération d'un nombre entre 0 et LONGUEUR_FENETRE/LONGUEUR_TETE ou
    //LARGEUR_FENETRE/LONGUEUR_TETE
    //garantir la génération arbitraire des nombres
    srand(time(NULL));
    int random_x = rand() % ((int)floor(LONGUEUR_FENETRE/LONGUEUR_TETE/2));
    int random_y = rand() % ((int)floor(LARGEUR_FENETRE/LONGUEUR_TETE/2));
    //ensuite on le multiplie par LONGUEUR_FENETRE ou LARGEUR_FENETRE
    //pour garantir que la tête du serpent et le fruit soient allignés
    random_x = random_x*LONGUEUR_TETE;
    random_y = random_y*LONGUEUR_TETE;
    setRect(2,2,LONGUEUR_TETE - 3,LONGUEUR_TETE -3);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
    setPos(random_x, random_y);
    game->getScene()->addItem(this);
    qDebug() << "x: " << random_x << " , y: "<< random_y;


    //m_score = 1;
}
/*
int Fruit::getX(){
    return this->getX();
}
int Fruit::getY(){
    return this->getY();
}
*/
