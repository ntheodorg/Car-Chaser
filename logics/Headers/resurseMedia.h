#ifndef RESURSEMEDIA_H_INCLUDED
#define RESURSEMEDIA_H_INCLUDED

#include <windows.h>
#include <mmsystem.h>
#define SUNET_BUTON "bin//Audio//Buton_soundEffect.wav"
#define SUNET_EXIT "bin//Audio//Exit_Button.wav"

bool fisiereDeSunet=1;

void existaFisiereDeSunet()
{
    FILE *fptr;
    if ((fptr = fopen("bin//Audio//Buton_soundEffect.wav","r")) != NULL)
    {
        if ((fptr = fopen("bin//Audio//Exit_Button.wav","r")) != NULL)
            fisiereDeSunet=1;
    }
    else if ((fptr = fopen("logics//bin//Audio//Buton_soundEffect.wav","r")) != NULL)
    {
        if ((fptr = fopen("logics//bin//Audio//Exit_Button.wav","r")) != NULL)
            {
                #undef SUNET_BUTON
                #undef SUNET_EXIT
                #define SUNET_BUTON "logics//bin//Audio//Buton_soundEffect.wav"
                #define SUNET_EXIT "logics//bin//Audio//Exit_Button.wav"
            }
    }
    else
        fisiereDeSunet=0;
}

void efectSonor(char* text)
{
    if(fisiereDeSunet)
    {
        if(!strcmp(text,"buton"))
            PlaySound(SUNET_BUTON,NULL,SND_ASYNC);
        if(!strcmp(text,"iesire"))
            PlaySound(SUNET_EXIT,NULL,SND_SYNC);
    }
}

#endif // RESURSEMEDIA_H_INCLUDED
