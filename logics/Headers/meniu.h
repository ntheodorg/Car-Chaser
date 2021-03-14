#ifndef MENIU_H_INCLUDED
#define MENIU_H_INCLUDED

#include "consola.h"
#include "culori.h"
#include "butoane.h"
#include "resurseMedia.h"

void Iesire()
{
        setactivepage(3);//ACTIVARE PAGINA NEFOLOSITA
        cleardevice();//CURATARE ECRAN
        setbkcolor(BGColor);
        setcolor(PColor);
        outtextxy(getmaxx()/2,getmaxy()/2,"EXITING...");
        setvisualpage(3);//AFISARE ACEEASI PAGINA
        efectSonor("iesire");
        //DE IMPLEMENTAT SALVAREA LISTELOR <<<<<<<<<<--------------------
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
        /*listaSimpla*/
        dinamicaButon(x,y,8,indexPagina,111);
        //
        /*listaDubla*/
        dinamicaButon(x,y,9,indexPagina,112);
        //
        /*Stiva*/
        dinamicaButon(x,y,10,indexPagina,113);
        //
        /*Coada*/
        dinamicaButon(x,y,11,indexPagina,114);
        //
        /*BACK*/
        dinamicaButon(x,y,7,indexPagina,1);
        //
        break;
    /**/
    /*/**LISTE**/
    /*case 111:
        //if(!consolaAfisata) mutaConsola(),consolaAfisata=1;
        main_listaSimpla();
        setcurrentwindow(window);
        initiereTextSettings();
        indexPagina=11;
        break;
    /**/
    /**LISTE**/
    /*case 112:
        //if(!consolaAfisata) mutaConsola(),consolaAfisata=1;
        main_listaDubla();
        setcurrentwindow(window);
        initiereTextSettings();
        indexPagina=11;
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
