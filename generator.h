#ifndef GENERATOR_H
#define GENERATOR_H
#include <iostream>

using namespace std;

struct komorka{
    bool odwiedzone;
    bool sciana_gora;
    bool sciana_dol;
    bool sciana_lewo;
    bool sciana_prawo;
    char znak;
};
void start();
void inicjuj();
void zapisz();
void generuj();
void przerysuj();

#endif // GENERATOR_H
