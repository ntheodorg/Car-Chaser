#ifndef BUTOANE_H_INCLUDED
#define BUTOANE_H_INCLUDED

#include <graphics.h>
#include "resurseMedia.h"
#include "culori.h"
#define MAX_BUTOANE 12
#define EROARE 10000 // Numarul de butoane este mic

struct butonBP
{
    int x_mij,y_mij,w,h;
    char* text;
    void creareButon(int, int, char*);
}buton[MAX_BUTOANE];

void butonBP::creareButon(int x, int y, char* text)
{
    int W,H,w,h;
    textsettingstype textinfo;
    gettextsettings(&textinfo);
    W=(strlen(text)+1)*(textinfo.charsize+6);
    H=(textinfo.charsize)*4;
    w=W/2,h=H/2;
    this->x_mij=x;
    this->y_mij=y;
    this->w=w;
    this->h=h;
    this->text=text;
}
void initiereButoane()
{
    int mx=getmaxx()/2;
    int my=getmaxy()/2;
    int spatiuDintreButoane=50;
    /**INCEPE**/
    buton[1].creareButon(mx,my-spatiuDintreButoane,"INCEPE");
    /**/
    /**SETARI**/
    buton[2].creareButon(mx,my+spatiuDintreButoane,"SETARI");
    /**/
    /**IESIRE**/
    buton[3].creareButon(mx,my+spatiuDintreButoane*3,"IESIRE");
    /**/
    /**CULORI**/
    buton[4].creareButon(mx,my-spatiuDintreButoane,"CULORI");
    /**/
    /**LIMBA**/
    buton[5].creareButon(mx,my+spatiuDintreButoane,"LIMBA");
    /**/
    /**VITEZA**/
    buton[6].creareButon(mx,my+spatiuDintreButoane*3,"VITEZA");
    /**/
    /**SET 1 - CULORI**/
    buton[10].creareButon(mx,my-spatiuDintreButoane,"CLASIC");
    /**/
    /**SET 2 - CULORI**/
    buton[11].creareButon(mx,my+spatiuDintreButoane,"SET 2");
    /**/
    /**SET 3 - CULORI**/
    buton[12].creareButon(mx,my+spatiuDintreButoane*3,"SET 3");
    /**/
    /**INVERT - CULORI**/
    buton[13].creareButon(mx,my-(spatiuDintreButoane*4),"INVERT");
    /**/
    /**INAPOI**/
    buton[7].creareButon(1,1,"INAPOI");
    buton[7].x_mij=0+buton[7].w;
    buton[7].y_mij=getmaxy()-buton[7].h;
    /**/
}

void puneButon(butonBP &buton)
{
    int x=buton.x_mij,y=buton.y_mij,w=buton.w,h=buton.h;
    char* text=buton.text;
    int poly[]={x-w,y-h,x-w,y+h,x+w,y+h,x+w,y-h,x-w,y-h};
    setcolor(culori.PColor);
    setfillstyle(SOLID_FILL,culori.BGColor);
    fillpoly(5,poly);
    y+=16; //CENTRARE TEXT IN CHENARUL-BUTTON
    outtextxy(x,y,text);
}

void puneButon_hover(butonBP &buton)
{
    int x=buton.x_mij,y=buton.y_mij,w=buton.w,h=buton.h;
    char* text=buton.text;
    int poly[]={x-w,y-h,x-w,y+h,x+w,y+h,x+w,y-h,x-w,y-h};
    setbkcolor(culori.PColor);
    setcolor(culori.BGColor);
    setfillstyle(SOLID_FILL,culori.PColor);
    fillpoly(5,poly);
    y+=16; //CENTRARE TEXT IN CHENARUL-BUTTON
    outtextxy(x,y,text);
    setbkcolor(culori.BGColor);
}

bool suntCoordonatelePeButon(int x, int y, butonBP buton)
{
    if(x >= (buton.x_mij-buton.w) && x <= (buton.x_mij+buton.w) && y >= (buton.y_mij-buton.h) && y <= (buton.y_mij+buton.h))
        return true;
    return false;
}

void dinamicaButon(int x, int y, int indexButon, int &indexPaginaCurenta, int indexPaginaDestinatie)
{
    puneButon(buton[indexButon]);
    if(suntCoordonatelePeButon(x,y,buton[indexButon]))
    {
        puneButon_hover(buton[indexButon]);
        getmouseclick(WM_LBUTTONUP,x,y);
        if(suntCoordonatelePeButon(x,y,buton[indexButon]))
            efectSonor("buton"),indexPaginaCurenta=indexPaginaDestinatie;
    }
}
void dinamicaButonCulori(int x, int y, int indexButon, int newBGColor, int newPColor)
{
    puneButon(buton[indexButon]);
    if(suntCoordonatelePeButon(x,y,buton[indexButon]))
    {
        puneButon_hover(buton[indexButon]);
        getmouseclick(WM_LBUTTONUP,x,y);
        if(suntCoordonatelePeButon(x,y,buton[indexButon]))
        {
            efectSonor("buton");
            culori.BGColor = newBGColor;
            culori.PColor = newPColor;
        }
    }
}
void dinamicaButonCuloriInvert(int x, int y, int indexButon)
{
    int aux;
    puneButon(buton[indexButon]);
    if(suntCoordonatelePeButon(x,y,buton[indexButon]))
    {
        puneButon_hover(buton[indexButon]);
        getmouseclick(WM_LBUTTONUP,x,y);
        if(suntCoordonatelePeButon(x,y,buton[indexButon]))
        {
            efectSonor("buton");
            aux = culori.BGColor;
            culori.BGColor = culori.PColor;
            culori.PColor = aux;
        }
    }
}



#endif // BUTOANE_H_INCLUDED
