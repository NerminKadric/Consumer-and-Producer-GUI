#ifndef PROIZVODJAC_H
#define PROIZVODJAC_H


#include <QThread>
#include <QObject>
#include <QSemaphore>


class Proizvodjac : public QThread
{
    Q_OBJECT
public:
    explicit Proizvodjac(QObject *parent);
    void run();
signals:
    void promjenaProizvedenih(int);
    void promjenaNapunjenihBuffera(int);
    void posaljiSlovo(char);

};

#endif // PROIZVODJAC_H
