#ifndef MENIU_H_INCLUDED
#define MENIU_H_INCLUDED

#include "consola.h"
#include "culori.h"
#include "butoane.h"
#include "resurseMedia.h"
#include "joc.h"

void Iesire()
{
        setactivepage(3);//ACTIVARE PAGINA NEFOLOSITA
        cleardevice();//CURATARE ECRAN
        setbkcolor(BGColor);
        setcolor(PColor);
        outtextxy(getmaxx()/2,getmaxy()/2,"EXITING...");
        setvisualpage(3);//AFISARE ACEEASI PAGINA
        efectSonor("iesire");
        closegraph();//INCHIDERE GRAPH
        afiseazaConsola();//AFISEAZA CONSOLA
        exit(0);//IESIRE DIN PROGRAM
}

void afisareMeniu(int &indexPagina)
{
    int x,y; //COORDONATE PENTRU MOUSE
    bool consolaAfisata=1;
    x=mousex(),y=mousey(); //VERIFICA POZITIA MOUSE-ULUI LA FIECARE CADRU
    setbkcolor(BGColor);
    if(consolaAfisata) ascundeConsola(),consolaAfisata=0; //ascunde
    switch(indexPagina)
    {
    /**INCEPE & SETARI & IESIRE**/
    case 1:
        /*INCEPE*/
        dinamicaButon(x,y,1,indexPagina,11);
        //
        /*SETARI*/
        dinamicaButon(x,y,2,indexPagina,12);
        //
        /*IESIRE*/
        dinamicaButon(x,y,3,indexPagina,-1);
        break;
    /**/
    /**CULORI & LIMBA & VITEZA & BACK**/
    case 12:
        /*CULORI*/
        dinamicaButon(x,y,4,indexPagina,12);
        //
        /*LIMBA*/
        dinamicaButon(x,y,5,indexPagina,12);
        //
        /*VITEZA*/
        dinamicaButon(x,y,6,indexPagina,12);
        //
        /*BACK*/
        dinamicaButon(x,y,7,indexPagina,1);
        //
        break;
    /**/
    /**MENIU DE LISTE**/
    case 11:
        if(!joc()) indexPagina=1;
        //buton e dupa ce moare
        break;
    /**/
    /**IESIRE**/
    case -1:
        Iesire();
        break;
    /**/
    }
}


#endif // MENIU_H_INCLUDED
