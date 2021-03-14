#ifndef JOC_H_INCLUDED
#define JOC_H_INCLUDED

int time=-1;

struct strat
{
    int x,y;
};

void crearePlansa()
{

}

void fata(int x, int y)
{
    fillellipse(x,y,20,20);
    putpixel(x+6,y-13,PColor);
    putpixel(x+6,y-11,PColor);
    putpixel(x-6,y-13,PColor);
    putpixel(x-6,y-11,PColor);
    line(x+7,y-12,x+5,y-12);
    line(x-7,y-12,x-5,y-12);
}

void animatieOm(int x, int y, bool jocTerminat)
{
    int stare=1;
    if(!jocTerminat)time+=2;
    if(time>=0 && time<100) stare=1;
    else if(time>=100 && time<=199) stare=2;
    else if(time>199) time=0;
    if(stare==1)
    {
        line(x-30,y+15,x-30,y);
        line(x+30,y-15,x+30,y-30);
        line(x,y,x-30,y+15);
        line(x,y,x+30,y-15);
        fata(x,y);
    }
    else if(stare==2)
    {
        line(x-30,y-15,x-30,y-30);
        line(x,y,x-30,y-15);
        line(x+30,y+15,x+30,y);
        line(x,y,x+30,y+15);
        fata(x,y);
    }
}

bool joc()
{
    bool jocTerminat=0;
    strat straturi[3];
    crearePlansa();
    animatieOm(200,200,jocTerminat);
    return jocTerminat;
}

#endif // JOC_H_INCLUDED
