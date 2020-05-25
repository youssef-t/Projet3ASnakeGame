#include "snakeHead.h"

SnakeHead::SnakeHead()
{
    m_length_head = LENGTH_HEAD;
    setRect(0,0,40,40);
    setPos(LONGUEUR_FENETRE/2, LARGEUR_FENETRE/2);
    setFlag(QGraphicsItem::ItemIsFocusable);

}

void SnakeHead::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right)
        setPos(x() + m_length_head, y());
    else if(event->key() == Qt::Key_Left)
        setPos(x() - m_length_head, y());
    else if(event->key() == Qt::Key_Up)
        setPos(x(), y() - m_length_head);
    else if(event->key() == Qt::Key_Down)
        setPos(x(), y() + m_length_head);
}
