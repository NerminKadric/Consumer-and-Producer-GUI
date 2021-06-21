#include "dialog.h"
#include "ui_dialog.h"

#include "zajednickevarijable.h"

char buffer[velicinaBuffera];
QSemaphore slobodniBajti(velicinaBuffera);
QSemaphore iskoristeniBajti;
QString s;
int brojPozivaPomjeriElement = 0;
int brojPozivaPomjeriElementPotrosaca = -2;
int brojPozivaProizvodjac = 0;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    scena = new QGraphicsScene(this);

    ui->graphicsView->setScene(scena);
    scena->setSceneRect(0,0,1150,500);
    potrosac = new Potrosac(this);
    proizvodjac = new Proizvodjac(this);

    potrosac->start();
    proizvodjac->start();

    timerProizvodjac = new QTimer(this);
    timerPotrosac = new QTimer(this);
    QPen crna_olovka(Qt::black);
    QBrush zelena_cetka(Qt::green);
    QBrush zuta_cetka(Qt::yellow);
    QBrush crvena_cetka(Qt::red);

    QFont font("Times New Roman", 16);
    font.setBold(true);


    QGraphicsRectItem *item = new QGraphicsRectItem;
    item->setRect(QRect(0,0,50,50));
    item->setBrush(zuta_cetka);


    scena->addRect(50,50,150,150,crna_olovka,zelena_cetka)->setZValue(10);
    scena->addRect(800,50,150,150,crna_olovka,crvena_cetka)->setZValue(10);
    QGraphicsTextItem *zelena = scena->addText("Proizvodjac");
    zelena->setZValue(11);
    zelena->setPos(70,110);
    zelena->setDefaultTextColor(Qt::yellow);
    zelena->setFont(font);
    QGraphicsTextItem *zuta = scena->addText("Potrosac");
    zuta->setZValue(11);
    zuta->setPos(830,110);
    zuta->setDefaultTextColor(Qt::yellow);
    zuta->setFont(font);

    scena->addLine(250,400,750,400)->setZValue(10);
    scena->addLine(250,400,250,300)->setZValue(10);
    scena->addLine(350,400,350,300)->setZValue(10);
    scena->addLine(450,400,450,300)->setZValue(10);
    scena->addLine(550,400,550,300)->setZValue(10);
    scena->addLine(650,400,650,300)->setZValue(10);
    scena->addLine(750,400,750,300)->setZValue(10);

    QGraphicsTextItem *buff = scena->addText("Buffer");
    buff->setFont(font);
    buff->setPos(475,415);

    connect(timerProizvodjac, SIGNAL(timeout()),this,SLOT(pomjeriElementProizvodjaca()));

    connect(timerPotrosac,SIGNAL(timeout()),this,SLOT(pomjeriElementPotrosaca()));

    connect(potrosac,SIGNAL(promjenaNapunjenihBuffera(int)),this,SLOT(promjenaVrijednostiBuffera(int)));

    connect(proizvodjac,SIGNAL(promjenaNapunjenihBuffera(int)),this,SLOT(promjenaVrijednostiBuffera(int)));

    connect(proizvodjac,SIGNAL(posaljiSlovo(char)),this,SLOT(primiSlovo(char)));

    rectItem[0] = new QGraphicsRectItem();
    rectItem[1] = new QGraphicsRectItem();
    rectItem[2] = new QGraphicsRectItem();
    rectItem[3] = new QGraphicsRectItem();
    rectItem[4] = new QGraphicsRectItem();

    rectItem[0]->setBrush(Qt::yellow);
    rectItem[1]->setBrush(Qt::yellow);
    rectItem[2]->setBrush(Qt::yellow);
    rectItem[3]->setBrush(Qt::yellow);
    rectItem[4]->setBrush(Qt::yellow);

    myProxy[0] = new QGraphicsProxyWidget(rectItem[0]);
    myProxy[1] = new QGraphicsProxyWidget(rectItem[1]);
    myProxy[2] = new QGraphicsProxyWidget(rectItem[2]);
    myProxy[3] = new QGraphicsProxyWidget(rectItem[3]);
    myProxy[4] = new QGraphicsProxyWidget(rectItem[4]);


    animation1 = new QPropertyAnimation(myProxy[0],"geometry");
    animation2 = new QPropertyAnimation(myProxy[1],"geometry");
    animation3 = new QPropertyAnimation(myProxy[2],"geometry");
    animation4 = new QPropertyAnimation(myProxy[3],"geometry");
    animation5 = new QPropertyAnimation(myProxy[4],"geometry");

    animation6 = new QPropertyAnimation(myProxy[0],"geometry");
    animation7 = new QPropertyAnimation(myProxy[1],"geometry");
    animation8 = new QPropertyAnimation(myProxy[2],"geometry");
    animation9 = new QPropertyAnimation(myProxy[3],"geometry");
    animation10 = new QPropertyAnimation(myProxy[4],"geometry");

    connect(potrosac,SIGNAL(promjenaPotrosenih(int)),this,SLOT(promjenaVrijednostiPotrosaca(int)));

    connect(proizvodjac,SIGNAL(promjenaProizvedenih(int)),this,SLOT(promjenaVrijednostiProizvodjaca(int)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::promjenaVrijednostiBuffera(int)
{
    if(slobodniBajti.available())
    {
        qDebug() << "U bufferu ima slobodnih : " <<slobodniBajti.available() << " mjesta!";
    }else{
        qDebug() << "U bufferu nema slobodnih mjesta!";
    }

}

void Dialog::promjenaVrijednostiProizvodjaca(int broj)
{
    labelSlova[0] = new QLabel();
    labelSlova[1] = new QLabel();
    labelSlova[2] = new QLabel();
    labelSlova[3] = new QLabel();
    labelSlova[4] = new QLabel();

    qDebug() << "Kreirano slovo: " << s;

    if(brojPozivaProizvodjac == 1)
    {
        labelSlova[0]->setText(s);
        labelSlova[0]->setStyleSheet("QLabel { background-color: yellow;}");
        labelSlova[0]->setAlignment(Qt::AlignCenter);
        rectItem[0]->setFlag(QGraphicsItem::ItemIsMovable);

        myProxy[0]->setWidget(labelSlova[0]);
        myProxy[0]->setPos(150,150);


        scena->addItem(rectItem[0]);
    }else if(brojPozivaProizvodjac == 2)
    {
        labelSlova[1]->setText(s);
        labelSlova[1]->setStyleSheet("QLabel { background-color: yellow;}");
        labelSlova[1]->setAlignment(Qt::AlignCenter);
        rectItem[1]->setFlag(QGraphicsItem::ItemIsMovable);

        myProxy[1]->setWidget(labelSlova[1]);
        myProxy[1]->setPos(150,150);
        scena->addItem(rectItem[1]);
    }else if(brojPozivaProizvodjac == 3)
    {
        labelSlova[2]->setText(s);
        labelSlova[2]->setStyleSheet("QLabel { background-color: yellow;}");
        labelSlova[2]->setAlignment(Qt::AlignCenter);
        rectItem[2]->setFlag(QGraphicsItem::ItemIsMovable);

        myProxy[2]->setWidget(labelSlova[2]);
        myProxy[2]->setPos(150,150);
        scena->addItem(rectItem[2]);
    }else if(brojPozivaProizvodjac == 4)
    {
        labelSlova[3]->setText(s);
        labelSlova[3]->setStyleSheet("QLabel { background-color: yellow;}");
        labelSlova[3]->setAlignment(Qt::AlignCenter);
        rectItem[3]->setFlag(QGraphicsItem::ItemIsMovable);

        myProxy[3]->setWidget(labelSlova[3]);
        myProxy[3]->setPos(150,150);
        scena->addItem(rectItem[3]);
    }else if(brojPozivaProizvodjac == 5)
    {
        labelSlova[4]->setText(s);
        labelSlova[4]->setStyleSheet("QLabel { background-color: yellow;}");
        labelSlova[4]->setAlignment(Qt::AlignCenter);
        rectItem[4]->setFlag(QGraphicsItem::ItemIsMovable);

        myProxy[4]->setWidget(labelSlova[4]);
        myProxy[4]->setPos(150,150);
        scena->addItem(rectItem[4]);
        brojPozivaProizvodjac = 0;
    }


    brojPozivaProizvodjac++;
    if(slobodniBajti.available() > 0){
        timerProizvodjac->singleShot(200,this,SLOT(pomjeriElementProizvodjaca()));
        qDebug() << "Timer proizvodjac pokrenut.";
    }else{
        qDebug() << "U bufferu nema slobodnih mjesta, tako da timerProizvodjac nije pokrenut.";
    }

}

void Dialog::promjenaVrijednostiPotrosaca(int broj)
{
    for(int i = 0; i < 5; i++)
    {
        if(!buffer[i] == '\0')
        {
            timerPotrosac->singleShot(0,this,SLOT(pomjeriElementPotrosaca()));

        }
    }
    brojPozivaPomjeriElementPotrosaca++;

}

void Dialog::primiSlovo(char slovo)
{
    s = slovo;
}

void Dialog::pomjeriElementProizvodjaca()
{
    qDebug() << "Broj poziva pomjeri elementi = " << brojPozivaPomjeriElement;
    if(brojPozivaPomjeriElement == 1)
    {

        animation5->stop();

        animation1->setDuration(500);
        animation1->setStartValue(QRect(200,100,50,50));
        animation1->setKeyValueAt(0.1,QRect(275,100,50,50));
        animation1->setEndValue(QRect(275,350,50,50));

        animation1->start();

    }else if(brojPozivaPomjeriElement == 2)
    {
        animation1->stop();

        animation2->setDuration(500);
        animation2->setStartValue(QRect(200,100,50,50));
        animation2->setKeyValueAt(0.1,QRect(375,100,50,50));
        animation2->setEndValue(QRect(375,350,50,50));
        animation2->start();

    }else if(brojPozivaPomjeriElement == 3)
    {
        animation2->stop();

        animation3->setDuration(500);
        animation3->setStartValue(QRect(200,100,50,50));
        animation3->setKeyValueAt(0.1,QRect(475,100,50,50));
        animation3->setEndValue(QRect(475,350,50,50));
        animation3->start();

    }else if(brojPozivaPomjeriElement == 4)
    {
        animation3->stop();

        animation4->setDuration(500);
        animation4->setStartValue(QRect(200,150,50,50));
        animation4->setKeyValueAt(0.1,QRect(575,100,50,50));
        animation4->setEndValue(QRect(575,350,50,50));
        animation4->start();

    }else if(brojPozivaPomjeriElement == 5)
    {
        animation4->stop();

        animation5->setDuration(500);
        animation5->setStartValue(QRect(200,100,50,50));
        animation5->setKeyValueAt(0.1,QRect(675,100,50,50));
        animation5->setEndValue(QRect(675,350,50,50));
        animation5->start();

        brojPozivaPomjeriElement = 0;
    }
    brojPozivaPomjeriElement++;

}

void Dialog::pomjeriElementPotrosaca()
{


    if(brojPozivaPomjeriElementPotrosaca == 1)
    {
        qDebug() << "Pomjeri Element potrosaca pozvan : " << brojPozivaPomjeriElementPotrosaca;
        animation6->setDuration(500);
        animation6->setStartValue(QRect(275,350,50,50));
        animation6->setKeyValueAt(0.1,QRect(275,100,50,50));
        animation6->setEndValue(QRect(800,100,50,50));
        animation6->start();
    }else if(brojPozivaPomjeriElementPotrosaca == 2)
    {
        qDebug() << "Pomjeri Element potrosaca pozvan: " << brojPozivaPomjeriElementPotrosaca;
        animation7->setDuration(500);
        animation7->setStartValue(QRect(375,350,50,50));
        animation7->setKeyValueAt(0.1,QRect(375,100,50,50));
        animation7->setEndValue(QRect(800,100,50,50));
        animation7->start();
    }else if(brojPozivaPomjeriElementPotrosaca == 3)
    {
        qDebug() << "Pomjeri Element potrosaca pozvan: " << brojPozivaPomjeriElementPotrosaca;

        animation8->setDuration(500);
        animation8->setStartValue(QRect(475,350,50,50));
        animation8->setKeyValueAt(0.1,QRect(475,100,50,50));
        animation8->setEndValue(QRect(800,100,50,50));
        animation8->start();
    }else if(brojPozivaPomjeriElementPotrosaca == 4)
    {
        qDebug() << "Pomjeri Element potrosaca pozvan: " << brojPozivaPomjeriElementPotrosaca;

        animation9->setDuration(500);
        animation9->setStartValue(QRect(575,350,50,50));
        animation9->setKeyValueAt(0.1,QRect(575,100,50,50));
        animation9->setEndValue(QRect(800,100,50,50));
        animation9->start();
    }else if(brojPozivaPomjeriElementPotrosaca == 5)
    {
        qDebug() << "Pomjeri Element potrosaca pozvan: " << brojPozivaPomjeriElementPotrosaca;

        animation10->setDuration(500);
        animation10->setStartValue(QRect(675,350,50,50));
        animation10->setKeyValueAt(0.1,QRect(675,100,50,50));
        animation10->setEndValue(QRect(800,100,50,50));
        animation10->start();
        brojPozivaPomjeriElementPotrosaca = 0;
    }


}
