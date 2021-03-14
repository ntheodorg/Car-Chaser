#ifndef CONSOLA_H_INCLUDED
#define CONSOLA_H_INCLUDED

HWND console = GetConsoleWindow();
RECT r;

void initConsola()
{
    GetWindowRect(console, &r); //stores the console's current dimensions
}

void ascundeConsola()
{
    ShowWindow(console, SW_HIDE );
    ShowWindow(FindWindow(NULL,"Bib_lis"), SW_SHOW );
}

void afiseazaConsola()
{
    ShowWindow(console, SW_SHOW);
    ShowWindow(FindWindow(NULL,"Bib_lis"), SW_HIDE);
}

#endif // CONSOLA_H_INCLUDED
