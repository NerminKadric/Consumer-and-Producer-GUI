#ifndef SLOVO1_H
#define SLOVO1_H

#include <QGraphicsItem>
#include <QString>
#include <QPixmap>
#include <QPainter>

class Slovo1 : public QGraphicsItem
{
public:
    QString novoSlovo;
    Slovo1(QString slovo);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public slots:
    void primiSlovo(char);
};

#endif // SLOVO1_H
