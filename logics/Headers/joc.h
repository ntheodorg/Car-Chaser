#ifndef JOC_H_INCLUDED
#define JOC_H_INCLUDED

#define MAX_STRATURI 3

struct strat
{
    int x,y;
};

struct om
{
    int x, y;
};

struct obstacol
{
    float x,y,speed;
    int W,H;
};

void crearePlansa(struct strat* arr, struct obstacol* lemne)
{
    arr[1].x=getmaxx()/2;
    arr[1].y=getmaxy()-100;
    arr[0].x=arr[1].x/2;
    arr[0].y=arr[1].y;
    arr[2].x=(getmaxx()+arr[1].x)/2;
    arr[2].y=arr[1].y;
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

void obstacol(int x, int y)
{
    int W=30,H=20;
    rectangle(x-W/2,y-H/2,x+W/2,y+H/2);
}

void generator(strat* arr, float & time)
{

}

void joc()
{
    struct om chaser;
    chaser.y=getmaxy()-100;

    struct obstacol lemne;

    setbkcolor(BGColor);
    setcolor(PColor);
    strat straturi[3];
    crearePlansa(straturi,&lemne);
    int page=3,controller=1,pauza=0;
    float globalTime=0,animTime=0; //ANIMTIME E DOAR PENTRU OM DEOCAMDATA
    //animatieOm(straturi[1].x,straturi[1].y); //press any key to start
    while(1)
    {
        setvisualpage(page);//AFISARE ACEEASI PAGINA
        setactivepage(7-page);//ACTIVARE PAGINA NEFOLOSITA
        cleardevice(); //GOLIRE PAGINA ACTIVA*/

        outtextxy(200,200,"ciorba");

        //generator(straturi,globalTime);//,lemne); //OBSTACOLELE


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
