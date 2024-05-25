#ifndef PRINTMENU_H
#define PRINTMENU_H

#include "Manager/ManagerLobby.h"
#include "Festivalier/FestivalierLobby.h"

#include <stdio.h>
#include <stdlib.h>
int option;

void printmenu()
{
    do
    {
        printf("Bienvenue\n");
        printf("1:Manager\n");
        printf("2:Festivalier\n");
        printf("Taper le chiffre correspondant a l'option pour choisir\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            managerlobby();
            break;
        case 2:
            festivalierlobby();
            break;
        default:
            printf("erreur\n");
            break;
        }
    } while (option < 1 || option > 2);
}
#endif