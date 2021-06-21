#ifndef ZAJEDNICKEVARIJABLE
#define ZAJEDNICKEVARIJABLE

const int kolicinaPodataka = 100;
const int velicinaBuffera = 5;
extern QString s;
extern int brojPozivaPomjeriElement;
extern int brojPozivaPomjeriElementPotrosaca;

extern int brojPozivaProizvodjac;

extern char buffer[velicinaBuffera];
extern QSemaphore slobodniBajti;
extern QSemaphore iskoristeniBajti;

#endif // ZAJEDNICKEVARIJABLE

