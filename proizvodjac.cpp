#include "proizvodjac.h"

#include "zajednickevarijable.h"

Proizvodjac::Proizvodjac(QObject *parent):QThread(parent)
{

}

void Proizvodjac::run()
{
    const int MAX = 26;
    char alphabet[MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };

    for(int i = 0; i < kolicinaPodataka; ++i)
    {

       char c;
       int r;
       r = qrand() % 25;
       c = 'A' + r;
       slobodniBajti.acquire();
       buffer[i%velicinaBuffera] = c;
       emit posaljiSlovo(c);
       iskoristeniBajti.release();

       this->msleep(3000);

           emit promjenaNapunjenihBuffera(iskoristeniBajti.available());
           emit promjenaProizvedenih(i);

    }
}
