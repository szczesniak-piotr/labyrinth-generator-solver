#include <iostream>
#include <ctime>
#include <fstream>
#include <limits>
#include "generator.h"
#include "wczytaj.h"

using namespace std;

void inicjuj(komorka **poziom,int rozmiar){
    for(int i=0; i<rozmiar; i++) {
                    for(int j=0; j<rozmiar; j++) {
                            poziom[i][j].znak = '#';
                            poziom[i][j].odwiedzone = false;
                            poziom[i][j].sciana_gora = true;
                            poziom[i][j].sciana_dol = true;
                            poziom[i][j].sciana_lewo = true;
                            poziom[i][j].sciana_prawo = true;
                    }
            }
            for(int i=1; i<rozmiar-1; i++) {
                    for(int j=1; j<rozmiar-1; j++) {
                            poziom[1][j].sciana_gora = false;
                            poziom[rozmiar-2][j].sciana_dol = false;
                            poziom[i][1].sciana_lewo = false;
                            poziom[i][rozmiar-2].sciana_prawo = false;
                    }
            }
}
void przerysuj(komorka **poziom,int rozmiar){
    for(int i=0;i<rozmiar;i++){
        for(int j=0;j<rozmiar;j++){
            cout << " " << poziom[i][j].znak;
        }
        cout << endl;
    }
}
void generuj(komorka **poziom,int rozmiar){
    srand(time(nullptr));
    int random = 0;
            int randomX = ((2*rand())+1)%(rozmiar-1);
            int randomY = ((2*rand())+1)%(rozmiar-1);
            int odwiedzone = 1;
            int wszystkiekomorki = ((rozmiar-1)/2)*((rozmiar-1)/2); //bez scian

            Backtrack *glowa=new Backtrack;
            glowa->next=nullptr;
            glowa->x=randomX;
            glowa->y=randomY;

            poziom[randomX][randomY].znak = 255;
            poziom[randomX][randomY].odwiedzone = true;                                         // Pierwsza komorka jako odwiedzona

            while( odwiedzone < wszystkiekomorki )
            {
                    if(((randomX-2>0)&&(poziom[randomX-2][randomY].odwiedzone == false) && (poziom[randomX][randomY].sciana_gora == true && poziom[randomX-2][randomY].sciana_dol == true)) ||
                       ((randomX+2<rozmiar-1)&&(poziom[randomX+2][randomY].odwiedzone == false) && (poziom[randomX][randomY].sciana_dol == true && poziom[randomX+2][randomY].sciana_gora == true)) ||
                       ((randomY-2>0)&&(poziom[randomX][randomY-2].odwiedzone == false) && (poziom[randomX][randomY].sciana_lewo == true && poziom[randomX][randomY-2].sciana_prawo == true)) ||
                       ((randomY+2<rozmiar-1)&&(poziom[randomX][randomY+2].odwiedzone == false) && (poziom[randomX][randomY].sciana_prawo == true && poziom[randomX][randomY+2].sciana_lewo == true)))
                    {
                            random = (rand() % 4) + 1;

                             // GORA
                            if((randomX-2>0)&&(random == 1) && (randomX > 1)) {
                                    if(poziom[randomX-2][randomY].odwiedzone == false) {        // Czy odwiedzone
                                            poziom[randomX-1][randomY].znak = 255;        // Usun hashtag
                                            poziom[randomX-1][randomY].odwiedzone = true;       // Zaznacz jako odzwiedzone
                                            poziom[randomX][randomY].sciana_gora = false;       // Usun sciane

                                            wstaw(glowa, randomX, randomY);

                                            randomX -= 2;                                   // Nastepna komorka
                                            poziom[randomX][randomY].odwiedzone = true;         // Zaznacz jako odwiedzona
                                            poziom[randomX][randomY].znak = 255;          // Usun hash
                                            poziom[randomX][randomY].sciana_dol = false;       // Usun sciane
                                            odwiedzone++;                                 // licznik++
                                    }
                                    else
                                            continue;
                            }

                            // DOL
                            else if((randomX+2<rozmiar-1)&&(random == 2) && (randomX < rozmiar-2)) {
                                    if(poziom[randomX+2][randomY].odwiedzone == false) {
                                            poziom[randomX+1][randomY].znak = 255;
                                            poziom[randomX+1][randomY].odwiedzone = true;
                                            poziom[randomX][randomY].sciana_dol = false;

                                            wstaw(glowa, randomX, randomY);

                                            randomX += 2;
                                            poziom[randomX][randomY].odwiedzone = true;
                                            poziom[randomX][randomY].znak = 255;
                                            poziom[randomX][randomY].sciana_gora = false;
                                            odwiedzone++;
                                    }
                                    else
                                            continue;
                            }

                            // LEWO
                            else if((randomY-2>0)&&(random == 3) && (randomY > 1)) {
                                    if(poziom[randomX][randomY-2].odwiedzone == false) {
                                            poziom[randomX][randomY-1].znak = 255;
                                            poziom[randomX][randomY-1].odwiedzone = true;
                                            poziom[randomX][randomY].sciana_lewo = false;

                                            wstaw(glowa, randomX, randomY);

                                            randomY -= 2;
                                            poziom[randomX][randomY].odwiedzone = true;
                                            poziom[randomX][randomY].znak = 255;
                                            poziom[randomX][randomY].sciana_prawo = false;
                                            odwiedzone++;
                                    }
                                    else
                                            continue;
                            }

                            // PRAWO
                            else if((randomY+2<rozmiar-1)&&(random == 4) && (randomY < rozmiar-2)) {
                                    if(poziom[randomX][randomY+2].odwiedzone == false) {
                                            poziom[randomX][randomY+1].znak = 255;
                                            poziom[randomX][randomY+1].odwiedzone = true;
                                            poziom[randomX][randomY].sciana_prawo = false;

                                            wstaw(glowa, randomX, randomY);

                                            randomY += 2;
                                            poziom[randomX][randomY].odwiedzone = true;
                                            poziom[randomX][randomY].znak = 255;
                                            poziom[randomX][randomY].sciana_lewo = false;
                                            odwiedzone++;
                                    }
                                    else
                                            continue;
                            }
                    }
                    else {
                        usun(glowa);
                        randomX=glowa->x;
                        randomY=glowa->y;
                    }
            }
            system("cls");
            przerysuj(poziom,rozmiar);
            cout << endl << "Generowanie zakonczone!" << endl;
}
void zapisz(komorka **poziom,int rozmiar){
    ofstream zapis;
            char plik[20];
            string wybor;
            cout << endl << "Zapisac? (T/N): ";
            cin >> wybor;

            if ((wybor[0] == 't') || (wybor[0] == 'T')) {
                    cout << endl << "Zapisac jako: ";
                    cin >> plik;
                    zapis.open(plik);
                    zapis << rozmiar;
                    for (int i = 0; i < rozmiar; i++) {
                        zapis << endl;
                        for (int j = 0; j < rozmiar; j++) {
                                zapis << poziom[i][j].znak << " ";
                        }
                    }
                    cout << "Labirynt zapisano jako: " << "\"" << plik << "\"" << endl;
                    zapis.close();
            }
}
void start(){
    int rozmiar;
    cout << "Podaj rozmiar, musi to byc liczba nieparzysta oraz wieksza niz 3: ";
    while( (!(cin >> rozmiar)) or (rozmiar<3) or (rozmiar%2==0) ){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Podaj poprawny rozmiar, musi to byc liczba nieparzysta oraz wieksza niz 3: ";
        }
    cout << endl << "Wczytano rozmiar" << endl;


    komorka **poziom=new komorka *[rozmiar];
    for(int i=0;i<rozmiar;i++){
        poziom[i]=new komorka [rozmiar];
    }

    bool koniec_gry=false;
    while(!koniec_gry){
        system("cls");
        inicjuj(poziom,rozmiar);
        przerysuj(poziom,rozmiar);
        generuj(poziom,rozmiar);
        zapisz(poziom,rozmiar);

        string wybor;
        cout << "Wygenerowac nowy labirynt (T/N)?" << endl;
        cin>>wybor;
        if((wybor[0] != 'n') && (wybor[0] != 'N') && (wybor[0] != 't') && (wybor[0] != 'T')){
            cout << "Nieprawidlowa opcja" << endl;
        }
        else{
            if((wybor[0] == 'n') || (wybor[0] == 'N')){
                koniec_gry = true;
            }
        }
    }
}

