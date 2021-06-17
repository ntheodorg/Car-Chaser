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
    bool traieste;
};

void crearePlansa(struct om& player, struct strat* arr, struct obstacol& lemne)
{
    player.W=40; //latime de coliziune
    player.H=50;    //inaltime de coliziune
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
    setfillstyle(SOLID_FILL,culori.BGColor);
    fillellipse(x,y,20,20);
    putpixel(x+6,y-13,culori.PColor);
    putpixel(x+6,y-11,culori.PColor);
    putpixel(x-6,y-13,culori.PColor);
    putpixel(x-6,y-11,culori.PColor);
    line(x+7,y-12,x+5,y-12);
    line(x-7,y-12,x-5,y-12);
}

void animatieOm(om& chaser, int x, float &time)
{
    int y=chaser.y;
    chaser.x=x;
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
        vect[i].traieste=1;
    }
    if(contor==MAX_STRATURI) vect[rand()%MAX_STRATURI+0].activ=false;
    return vect;
}
bool ok=0;
int obstacole(strat* arr, float &time, struct obstacol &lemne, obstacol *(&vect)[20], int &dimensiune,om chaser, int &scor)
{
    int lovit=0;
    int speed=5;
    obstacol* obs=new obstacol[MAX_STRATURI];
    if(time>1 || !ok)//&& time>10)
    {
        time=0,ok=1;
        /*GENERARE OBSTACOL*/
        ok=1,obs=generator(arr,lemne,obs);
        if(dimensiune>0)
        for(int i=dimensiune-1;i>=0;i--)
        {
            vect[i+1]=vect[i];
        }

        vect[0]=obs;

        if(dimensiune<19)
            dimensiune++;
        /*if(dimensiune==2)
            delete[] obs;*/
    }

   // sprintf(ceva,"%d %d %d",vect[0].y,vect[1].y,vect[2].y);
    //outtextxy(400,300,ceva);

   // for(int j=0;j<4;j++)
    for(int i=0;i<dimensiune;i++)
        for(int j=0;j<MAX_STRATURI;j++)
        {
            //obs[i].y+=speed;
            vect[i][j].y+=speed;
            if(vect[i][j].activ)
            {
                deseneaza(lemne,vect[i][j].x,vect[i][j].y);
                if(vect[i][j].y>=(chaser.y-(chaser.H/2)) && vect[i][j].y<=(chaser.y+(chaser.H/2)))
                    if(vect[i][j].x>=(chaser.x-(chaser.W/2)) && vect[i][j].x<=(chaser.x+(chaser.W/2)))
                    {
                        lovit=32;
                        break;
                    }
            }
            if(vect[i][j].y>=getmaxy()+vect[i][j].H && vect[i][j].y<=getmaxy()+vect[i][j].H+100)
            {
                if(vect[i][0].traieste!=0)
                {
                    delete[] vect[i],dimensiune--,scor++;
                    for(int k=0;k<MAX_STRATURI;k++)
                        vect[i][k].traieste=0;
                }
                break;
            }
        }
    return lovit;
}

void joc()
{
    setbkcolor(culori.BGColor);
    setcolor(culori.PColor);

    struct om chaser;
    chaser.y=getmaxy()-100;

    strat straturi[MAX_STRATURI];

    struct obstacol lemne;

    crearePlansa(chaser,straturi,lemne);

    obstacol *vect[20]={};
    int dimensiune=0;

    int page=3,controller=1,mort=0,scor=0,scorFinal;
    float globalTime=0,animTime=0,stopJoc=0;
    char ceva[1000];

    //animatieOm(straturi[1].x,straturi[1].y); //press any key to start
    while(1)
    {
        setvisualpage(page);//AFISARE ACEEASI PAGINA
        setactivepage(7-page);//ACTIVARE PAGINA NEFOLOSITA
        cleardevice(); //GOLIRE PAGINA ACTIVA*/



        if(!stopJoc)
        {
            if(!mort)
                mort=obstacole(straturi,globalTime,lemne,vect,dimensiune,chaser,scor); //OBSTACOLELE
            else
                obstacole(straturi,globalTime,lemne,vect,dimensiune,chaser,scor); //OBSTACOLELE

            if(mort!=32)
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

                sprintf(ceva,"%d",scor);
                outtextxy(getmaxx()/2,200,ceva);
                scorFinal=scor;

                animatieOm(chaser,straturi[controller].x,animTime);
            }
            if(dimensiune==0 && mort) stopJoc=1;
        }

        if(stopJoc)
        {

            globalTime+=0.1;

            outtextxy(getmaxx()/2,getmaxy()/2,"FELICITARI!");
            sprintf(ceva,"Scor: %d",scorFinal);
            outtextxy(getmaxx()/2,getmaxy()/2+50,ceva);

            if(globalTime > 1 && globalTime<=1.5)
            {
                outtextxy(getmaxx()/2,getmaxy()-200,"APASA   O   TASTA...");
            }
            if(globalTime>1.5)
            {
                getch();
                break;
            }
        }

        delay(10);
        page=7-page;
    }
}


#endif // JOC_H_INCLUDED
