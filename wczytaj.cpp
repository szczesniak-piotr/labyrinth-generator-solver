#include <fstream>
#include <stack>
#include <iostream>
#include <limits>

#include "menu.h"
#include "generator.h"
#include "wczytaj.h"

using namespace std;

void wstaw(Backtrack *&adres,int X,int Y){
    Backtrack *nowy=new Backtrack;
    nowy->next=adres;
    nowy->x=X;
    nowy->y=Y;
    adres=nowy;
}
void usun(Backtrack *&adres){
    Backtrack *tmp;
    tmp=adres;
    if(tmp){
        adres=tmp->next;
        delete tmp;
    }
}
//------------------------------------------------------------------------------------------------------------
void wczytaj_labirynt_lista()
{
    string nazwa,linijka,wybor;
    int xP,yP,xK,yK,n=0,rozmiar,dlugosc;
    cout << "Podaj rozmiar wczytywanego labiryntu, musi to byc liczba nieparzysta oraz wieksza niz 3: ";
    while( (!(cin >> rozmiar)) or (rozmiar<3) or (rozmiar%2==0) ){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Podaj poprawny rozmiar, musi to byc liczba nieparzysta oraz wieksza niz 3: ";
        }
    cout << endl << "Wczytano rozmiar" << endl;
    char **labirynt=new char *[rozmiar];

    for(int i=0;i<rozmiar;i++){
        labirynt[i]=new char [rozmiar];
    }

    Droga **labiryntliczby=new Droga *[rozmiar];

    for(int i=0;i<rozmiar;i++){
        labiryntliczby[i]=new Droga [rozmiar];
    }

    cout<< endl << "Podaj nazwe/sciezke pliku z labiryntem do wczytania" << endl;
    cin>> nazwa;

    ifstream plik;
    plik.open(nazwa);

        if(plik.good()){
            plik >> dlugosc;
            if(dlugosc!=rozmiar){
                cout << "Wczytany rozmiar jest inny niz podanego pliku. Przenosze do menu" << endl;
                menu();
            }
            while (!plik.eof())
            {
                getline(plik, linijka);
                for(int i=0;i<rozmiar;i++){
                    plik>>labirynt[n][i];
                }
                n++;
                }
        }else{
            cout << "Niepoprawna nazwa/sciezka pliku. Przenosze do menu" << endl << endl;
            menu();
        }
    cout << endl;
    cout<<"Wczytano poprawnie labirynt"<<endl<<endl;
    for(int i=0;i<rozmiar;i++){
        for(int j=0;j<rozmiar;j++){
            cout << " " <<labirynt[i][j];
        }
        cout << endl;
    }
    ret:
    //--------------------------------------------------------------------------
    cout<<"Wybierz koordynaty punktu startowego [x,y]"<<endl;
    cout<<"Podaj X"<<endl;
    cin>>xP;
    while(xP<1 or xP>rozmiar-2){
        cout<<"Podaj inna wspolrzedna X"<<endl;
        cin>>xP;
    }
    cout<<"Podaj Y"<<endl;
    cin>>yP;
    while(yP<1 or yP>rozmiar-2){
        cout<<"Podaj inna wspolrzedna Y"<<endl;
        cin>>yP;
    }
    //--------------------------------------------------------------------------
    cout<<"Wybierz koordynaty punktu koncowego [x,y]"<<endl;
    cout<<"Podaj X"<<endl;
    cin>>xK;
    while(xK<1 or xK>rozmiar-2){
        cout<<"Podaj inna wspolrzedna X"<<endl;
        cin>>xK;
    }
    cout<<"Podaj Y"<<endl;
    cin>>yK;
    while(yK<1 or yK>rozmiar-2){
        cout<<"Podaj inna wspolrzedna Y"<<endl;
        cin>>yK;
    }
    //--------------------------------------------------------------------------
    if(xP==xK and yP==yK){
        cout << "Podano identyczne koordynaty obu punktow." << endl;
        goto ret;
    }
    if(labirynt[xP][yP]=='#' or labirynt[xK][yK]=='#'){
        cout << "Podane koordynaty byly scianami" << endl;
        goto ret;
    }
    labirynt[xP][yP]='P';
    labirynt[xK][yK]='K';

    for(int i=0;i<rozmiar;i++){
        for(int j=0;j<rozmiar;j++){
            cout << " " <<labirynt[i][j];
        }
        cout << endl;
    }
    cout << "Czy potwierdzasz punkt startowy oraz koncowy? (T/N)" << endl;
    cin>>wybor;
    while(wybor[0]!='T' and wybor[0]!='t' and wybor[0]!='N' and wybor[0]!='n'){
        cout << "Niepoprawny wybor, prosze podac: (T/N)" << endl;
        cin>>wybor;
    }
    if(wybor[0]!='t' and wybor[0]!='T'){
        labirynt[xP][yP]=255;
        labirynt[xK][yK]=255;
        goto ret;
    }
    //--------------------------------------------------------------------------
    int pola = 0;
    for(int i=0;i<rozmiar;i++){
        for(int j=0;j<rozmiar;j++){
            if(labirynt[i][j]=='#'){
                labiryntliczby[i][j].liczba=1;
                labiryntliczby[i][j].odwiedzone=true;
            }
            else{
                labiryntliczby[i][j].liczba=0;
                pola++;
                labiryntliczby[i][j].odwiedzone=false;
            }
        }
    }
    {
    //for(int i=0;i<rozmiar;i++){
    //    for(int j=0;j<rozmiar;j++){
    //        cout << " " <<labiryntliczby[i][j].liczba;
    //    }
    //    cout << endl;
    //}
    cout << endl;
    }
    //--------------------------------------------------------------------------
    int odwiedzone=1,zachXP,zachYP;
    zachXP=xP;
    zachYP=yP;
    Backtrack *glowa=new Backtrack;
    glowa->next=nullptr;
    glowa->x=xP;
    glowa->y=yP;
    labiryntliczby[xP][yP].odwiedzone=true;

    while(xP!=xK or yP!=yK)
    {
        if(    (labiryntliczby[xP-1][yP].odwiedzone == false) or (labiryntliczby[xP+1][yP].odwiedzone == false) or
               (labiryntliczby[xP][yP-1].odwiedzone == false) or (labiryntliczby[xP][yP+1].odwiedzone == false) )
        {

                     // GORA
                     if((labiryntliczby[xP-1][yP].odwiedzone == false)&&(labiryntliczby[xP-1][yP].liczba == 0)) {
                                    labiryntliczby[xP-1][yP].liczba = labiryntliczby[xP][yP].liczba+1;
                                    labiryntliczby[xP-1][yP].odwiedzone = true;

                                    wstaw(glowa,xP,yP);

                                    xP -= 1;
                                    odwiedzone++;
                            }

                    // DOL
                    else if((labiryntliczby[xP+1][yP].odwiedzone == false)&&(labiryntliczby[xP+1][yP].liczba == 0)) {
                                    labiryntliczby[xP+1][yP].liczba = labiryntliczby[xP][yP].liczba+1;
                                    labiryntliczby[xP+1][yP].odwiedzone = true;

                                    wstaw(glowa,xP,yP);

                                    xP += 1;
                                    odwiedzone++;
                            }

                    // LEWO
                    else if((labiryntliczby[xP][yP-1].odwiedzone == false)&&(labiryntliczby[xP][yP-1].liczba == 0)) {
                                    labiryntliczby[xP][yP-1].liczba = labiryntliczby[xP][yP].liczba+1;
                                    labiryntliczby[xP][yP-1].odwiedzone = true;

                                    wstaw(glowa,xP,yP);

                                    yP -= 1;
                                    odwiedzone++;
                            }
                    // PRAWO
                    else if((labiryntliczby[xP][yP+1].odwiedzone == false)&&(labiryntliczby[xP][yP+1].liczba == 0)) {
                                    labiryntliczby[xP][yP+1].liczba = labiryntliczby[xP][yP].liczba+1;
                                    labiryntliczby[xP][yP+1].odwiedzone = true;

                                    wstaw(glowa,xP,yP);

                                    yP += 1;
                                    odwiedzone++;
                            }
            }else{
               usun(glowa);
               xP=glowa->x;
               yP=glowa->y;
            }
    }
    int liczbapol=labiryntliczby[xP][yP].liczba;
    while(xP!=zachXP or yP!=zachYP){
        if(glowa->x!=zachXP or glowa->y!=zachYP){
            labirynt[glowa->x][glowa->y]=254;
            xP=glowa->x;
            yP=glowa->y;
            usun(glowa);
        }
        else{
            break;
        }
    }
    cout << endl;
    for(int i=0;i<rozmiar;i++){
        for(int j=0;j<rozmiar;j++){
            cout << " " <<labirynt[i][j];
        }
        cout << endl;
    }
    cout << "Znaleziono najkrotsza droge w labiryncie, ma ona dlugosc: " << liczbapol << " pol" << endl;
    cout << endl;
    plik.close();
    cout << "Przeniesc do menu? (T/N)" << endl;
    cin >> wybor;
    while(wybor[0]!='T' and wybor[0]!='t' and wybor[0]!='N' and wybor[0]!='n'){
        cout << "Prosze podac prawidlowy wybor (T/N)" << endl;
        cin >> wybor;
    }
    if(wybor[0]=='t' or wybor[0]=='T'){
        menu();
    }
}






