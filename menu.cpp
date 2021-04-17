#include "menu.h"
#include "generator.h"
#include "wczytaj.h"
#include <iostream>

using namespace std;

void menu(){
    string wybor;
    cout << "~~~~~~~~ LABIRYNT ~~~~~~~~"<< endl << endl;
    cout << "PIOTR SZCZESNIAK PRODUCTION" << endl<<endl;
    cout<<"MENU: "<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"1. GENERUJ LABIRYNT"<<endl;
    cout<<"2. WCZYTAJ LABIRYNT"<<endl;
    cout<<"3. ZAKONCZ DZIALANIE"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
    cout<<"Podaj wybor:"<<endl;
    cin>> wybor;
    while(wybor[0]!='1' and wybor[0]!='2' and wybor[0]!='3'){
        cout<<"Podaj inny wybor:"<<endl;
        cin>> wybor;
    }
    if(wybor[0]=='1'){
        start();
        menu();
    }
    if(wybor[0]=='2'){
        wczytaj_labirynt_lista();
    }
}


