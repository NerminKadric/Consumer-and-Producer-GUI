#include "potrosac.h"
#include "zajednickevarijable.h"

Potrosac::Potrosac(QObject *parent):QThread(parent)
{

}

void Potrosac::run()
{
    for(int i = 0; i < kolicinaPodataka; ++i)
    {
        iskoristeniBajti.acquire();
        fprintf(stderr,"%c",buffer[i%velicinaBuffera]);


            if(slobodniBajti.available() == 5)
            {
                qDebug() << "Buffer je prazan totalno.";
            }else{
                slobodniBajti.release();
                this->msleep(3000);
                emit promjenaNapunjenihBuffera(iskoristeniBajti.available());
                 emit promjenaPotrosenih(i);
            }

    }
        fprintf(stderr,"\n");
}
