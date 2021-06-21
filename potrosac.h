#ifndef POTROSAC_H
#define POTROSAC_H

#include <QThread>
#include <QObject>
#include <QSemaphore>
#include <QDebug>

class Potrosac : public QThread
{
    Q_OBJECT
public:
    explicit Potrosac(QObject *parent = 0);
    void run();
signals:
    void promjenaNapunjenihBuffera(int);
    void promjenaPotrosenih(int);

};

#endif // POTROSAC_H
