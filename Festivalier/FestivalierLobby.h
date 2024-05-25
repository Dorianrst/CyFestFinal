#ifndef FESTIVALIERLOBBY_H
#define FESTIVALIERLOBBY_H

#include "../PrintMenu.h"
#include "PrintHall.h"
#include "Reserved.h"

#include <stdio.h>
#include <stdlib.h>
void festivalierlobby()
{
    int choice;
    printf("1: Afficahge des salles et des concerts\n ");
    printf("2: Reserver des places\n");
    printf("3: Menu\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printhall();
        break;

    case 2:
        reservedconcert();
        break;
    case 3:
        printmenu();
        break;
    default:
        // FestivalierLobby();
        break;
    }
}

#endif