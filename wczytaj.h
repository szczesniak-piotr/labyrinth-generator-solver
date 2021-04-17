#ifndef ZAPISZ_H
#define ZAPISZ_H
#include <iostream>

using namespace std;

struct Droga{
    int liczba;
    bool odwiedzone;
};
struct Backtrack{
    int x;
    int y;
    Backtrack *next;
};

void wstaw(Backtrack *&adres,int X,int Y);
void usun(Backtrack *&adres);
void wczytaj_labirynt_lista();

#endif // ZAPISZ_H
