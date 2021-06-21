#include "slovo1.h"


Slovo1::Slovo1(QString slovo)
{
    novoSlovo = slovo;
}

QRectF Slovo1::boundingRect() const
{
    return QRectF(50,50,100,100);
}



void Slovo1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen crna_olovka(Qt::black);
    painter->setPen(crna_olovka);
    QPixmap slovo1(50,50);
    slovo1.fill(Qt::yellow);
    painter->drawPixmap(200,200,50,50,slovo1);
}



