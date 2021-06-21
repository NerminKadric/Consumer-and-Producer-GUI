#ifndef DIALOG_H
#define DIALOG_H

#include <QDebug>
#include <QDialog>
#include "slovo1.h"
#include "proizvodjac.h"
#include "potrosac.h"
#include <QSemaphore>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRectF>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QGraphicsProxyWidget>
#include <QGraphicsItemAnimation>
#include <QPropertyAnimation>
#include <QFont>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
public slots:
    void promjenaVrijednostiBuffera(int);
    void promjenaVrijednostiProizvodjaca(int);
    void promjenaVrijednostiPotrosaca(int);
    void primiSlovo(char);
    void pomjeriElementProizvodjaca();
    void pomjeriElementPotrosaca();
private:
    QPropertyAnimation *animation1;
    QPropertyAnimation *animation2;
    QPropertyAnimation *animation3;
    QPropertyAnimation *animation4;
    QPropertyAnimation *animation5;

    QPropertyAnimation *animation6;
    QPropertyAnimation *animation7;
    QPropertyAnimation *animation8;
    QPropertyAnimation *animation9;
    QPropertyAnimation *animation10;

    QPainter *labelPainter;

    QGraphicsScene *scena;
    QGraphicsProxyWidget *myProxy[5];
    QGraphicsRectItem *rectItem[5];
    Ui::Dialog *ui;
    Slovo1 *slovo1;
    QTimer *timerPotrosac;
    QTimer *timerProizvodjac;
    QPainter *painterSlova;
    QRectF *slova[5];
    Proizvodjac *proizvodjac;
    Potrosac *potrosac;
    QLabel *labelSlova[5];

};

#endif // DIALOG_H
