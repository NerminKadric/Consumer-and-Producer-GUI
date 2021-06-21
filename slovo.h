#ifndef SLOVO_H
#define SLOVO_H

#include <QGraphicsItem>
#include <QLabel>
#include <QObject>
#include <proizvodjac.h>
#include <QPainter>


class Slovo : public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Slovo();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    Proizvodjac *proizvodjac;
    QLabel *label[5];
public slots:
    void promjenaVrijednostiProizvodjacaSlovo(int);

};

#endif // SLOVO_H
