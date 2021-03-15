#include <winbgim.h>
#include <graphics.h>
#include <iostream>
#include "Headers/meniu.h"
#include "Headers/textSettings.h"


using namespace std;

int main()
{
    cout<<endl;
    initwindow(800,1000,"Car-Chaser"); //mij ecranului
    initiereTextSettings();//INITIERE SETARILE DE STIL ALE TEXTULUI
    initiereButoane();//INITIALIZARE BUTOANELE DE MENIU
    existaFisiereDeSunet();//ACTIVARE SUNET(DACA FISIERELE SUNT LA LOCUL LOR)
    //initConsola();
    int paginaMeniu=1,page=0; //paginaMenu, 1 - PRIMA PAGINA A APLICATIEI
    do
    {
        setactivepage(page); //PAGINA CARE SE DESENEAZA IN SPATE CU URMATOARELE INSTRUCTIUNI DE DESEN
        setvisualpage(1-page); //PAGINA CARE SE AFISEAZA PENTRU CADRUL ALTERNAT INTRE 1 SI 0
        cleardevice(); //GOLIRE PAGINA ACTIVA*/

        afisareMeniu(paginaMeniu);

        delay(5);
        page=1-page; //ALTERNEAZA CADRUL INTRE 1 SI 0
    }while(1);
    return 0;
}
