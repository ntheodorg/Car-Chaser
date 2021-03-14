#ifndef RESURSEMEDIA_H_INCLUDED
#define RESURSEMEDIA_H_INCLUDED

#include <windows.h>
#include <mmsystem.h>

bool fisiereDeSunet=1;

void existaFisiereDeSunet()
{
    FILE *fptr;
    if ((fptr = fopen("bin//Audio//Buton_soundEffect.wav","r")) != NULL)
    {
        if ((fptr = fopen("bin//Audio//Exit_Button.wav","r")) != NULL)
            fisiereDeSunet=1;
    }
    else
        fisiereDeSunet=0;
}

void efectSonor(char* text)
{
    if(fisiereDeSunet)
    {
        if(!strcmp(text,"buton"))
            PlaySound("bin//Audio//Buton_soundEffect.wav",NULL,SND_ASYNC);
        if(!strcmp(text,"iesire"))
            PlaySound("bin//Audio//Exit_Button.wav",NULL,SND_SYNC);
    }
}

#endif // RESURSEMEDIA_H_INCLUDED
