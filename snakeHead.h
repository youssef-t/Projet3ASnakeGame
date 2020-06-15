#pragma once
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QBrush>
#include "constants.h"
#include "snakeBody.h"
#include <QList>
#include <QPointF>
#include <QString>
#include <QObject>
class SnakeHead : public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    //constructeur pour créer la tête du serpent
    SnakeHead();
    //méthode pour controler la tête
    void keyPressEvent(QKeyEvent* event);
    //bouger les blocs qui composent le corps
    void moveBody();
    //augmenter la taille du serpent
    void elongateBody();

    //retourner les coordonnées de la tête
    int getX();
    int getY();

public slots:
    void move();

private:
    //int m_length_head;
    QList<SnakeBody*> m_snake_body;
    //le premier bloc créé après la tête et qui compose le corps au début
    QPointF m_prev_pos;
    QString m_direction;
    QString m_direction_before_space;
    //détermine la vitesse du mouvement de la tête
    //en changeant la période du signal
    int m_periode;
    //gérer le mouvement de la tête de telle façon de ne pas sortir de la map
    void correction_position();
    //vérifier la position de la tête pour que le mouvement soit correct même si
    //l'utilisateur tape sur les touches de contrôle
    bool verify_position();

};

