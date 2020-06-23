#include "snakeBody.h"

/*SnakeBody est une classe fille de QGraphicsRectItem
  Alors on peut utiliser les méthodes que contient cette classe*/
SnakeBody::SnakeBody()
{
    setRect(0,0,LONGUEUR_TETE, LONGUEUR_TETE );
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor::fromRgb(39, 107, 173));
    setBrush(brush);

}
