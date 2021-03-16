#ifndef JOC_H_INCLUDED
#define JOC_H_INCLUDED

#include <stdlib.h>
#include <time.h>
#include <vector>

#define MAX_STRATURI 3

struct strat
{
    int x,y;
};

struct om
{
    int x, y, W, H;
};

struct obstacol
{
    int x, y, W, H;
    bool activ;
};

void crearePlansa(struct strat* arr, struct obstacol& lemne)
{
    arr[1].x=getmaxx()/2;
    arr[1].y=getmaxy()-100;
    arr[0].x=arr[1].x/2;
    arr[0].y=arr[1].y;
    arr[2].x=(getmaxx()+arr[1].x)/2;
    arr[2].y=arr[1].y;
    lemne.H=20;
    lemne.W=100;
    lemne.x=arr[1].x;
    lemne.y=0;
}

void fata(int x, int y)
{
    setfillstyle(SOLID_FILL,BGColor);
    fillellipse(x,y,20,20);
    putpixel(x+6,y-13,PColor);
    putpixel(x+6,y-11,PColor);
    putpixel(x-6,y-13,PColor);
    putpixel(x-6,y-11,PColor);
    line(x+7,y-12,x+5,y-12);
    line(x-7,y-12,x-5,y-12);
}

void animatieOm(om chaser, int x, float &time)
{
    int y=chaser.y;
    int stare=1;
    if(time>=0 && time<1) stare=1;
    else if(time>=1 && time<=1.99) stare=2;
    else if(time>1.99) time=0;
    if(stare==1)
    {
        line(x-30,y+15,x-30,y);
        line(x+30,y-15,x+30,y-30);
        line(x,y,x-30,y+15);
        line(x,y,x+30,y-15);
        fata(x+2,y);
    }
    else if(stare==2)
    {
        line(x-30,y-15,x-30,y-30);
        line(x,y,x-30,y-15);
        line(x+30,y+15,x+30,y);
        line(x,y,x+30,y+15);
        fata(x-2,y);
    }
}

void deseneaza(struct obstacol obiect,int x, int y)
{
    int W=obiect.W,H=obiect.H;
    rectangle(x-W/2,y-H/2,x+W/2,y+H/2);
    //drawpoly doar cu poly sa se face fiecare desen in functia asta
}


obstacol* generator(strat* arr,obstacol& lemne, obstacol* vect)
{
    srand(time(NULL));
    int numarGenerat,contor=0;
    for(int i=0;i<MAX_STRATURI;i++) //copiez marimea si schimb coordonatele
    {
        numarGenerat=rand()%100+0;
        if(numarGenerat%2==0)
        {
            contor++;
            vect[i].H=lemne.H;
            vect[i].W=lemne.W;
            vect[i].x=arr[i].x;
            vect[i].y=vect[i].H;
            vect[i].activ=1;
        }
        else
        {
            vect[i].x=0;
            vect[i].activ=0;
        }
    }
    if(contor==MAX_STRATURI) vect[rand()%MAX_STRATURI+0].activ=false;
    char ceva[1000];
    sprintf(ceva,"%d %d %d",vect[0].x,vect[1].x,vect[2].x);
    outtextxy(400,200,ceva);
    sprintf(ceva,"%d %d %d",vect[0].y,vect[1].y,vect[2].y);
    outtextxy(400,300,ceva);
    return vect;
}
bool ok=0;
void obstacole(strat* arr, float &time, struct obstacol &lemne, obstacol *(&vect)[20],int &dimensiune)
{
    int speed=2;
    if(time>1)//&& time>10)
    {
        time=0;
        /*GENERARE OBSTACOL*/
        obstacol* obs=new obstacol[MAX_STRATURI];
        ok=1,obs=generator(arr,lemne,obs);
        vect[dimensiune]=obs;
        if(dimensiune<20)
            dimensiune++;
       // delete[] obs;
    }

    char ceva[1000];
    sprintf(ceva,"%d %d %d",vect[0][0].activ,vect[0][1].activ,vect[0][2].activ);
    outtextxy(400,400,ceva);

   // for(int j=0;j<4;j++)
    for(int i=0;i<dimensiune;i++)
        for(int j=0;j<MAX_STRATURI;j++)
        {
            //obs[i].y+=speed;
            if(vect[i][j].activ)
                deseneaza(lemne,vect[i][j].x,vect[i][j].y+=speed);

            sprintf(ceva,"i%d  j%d  dim%d     %d %d %d",i,j,dimensiune,vect[i][j].x,vect[i][j].x,vect[i][j].x);
            outtextxy(400,500,ceva);
            //delay(1000);
        }
    //lemne.x
    //daca lemnele au ajuns jos delete
}

void joc()
{
    setbkcolor(BGColor);
    setcolor(PColor);

    struct om chaser;
    chaser.y=getmaxy()-100;

    strat straturi[MAX_STRATURI];

    struct obstacol lemne;

    crearePlansa(straturi,lemne);

    obstacol *vect[20];
    int dimensiune=0;

    int page=3,controller=1,pauza=0;
    float globalTime=0,animTime=0; //ANIMTIME E DOAR PENTRU OM DEOCAMDATA
    //animatieOm(straturi[1].x,straturi[1].y); //press any key to start
    while(1)
    {
        setvisualpage(page);//AFISARE ACEEASI PAGINA
        setactivepage(7-page);//ACTIVARE PAGINA NEFOLOSITA
        cleardevice(); //GOLIRE PAGINA ACTIVA*/

        outtextxy(200,200,"ciorba");

        obstacole(straturi,globalTime,lemne,vect,dimensiune); //OBSTACOLELE

        if(!pauza)
        {
            globalTime+=0.01;
            animTime+=0.01;
            if(kbhit())
            {
                switch(getch())
                {
                case 'd':
                case 77:
                    if(controller<MAX_STRATURI-1) controller++;
                    break;
                case 'a':
                case 75:
                    if(controller>0) controller--;
                    break;
                }
            }
            animatieOm(chaser,straturi[controller].x,animTime);
        }
        delay(5);
        page=7-page;
        if(globalTime> 100) break;
    }
}


#endif // JOC_H_INCLUDED
