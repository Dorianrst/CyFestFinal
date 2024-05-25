#ifndef MANAGERLOBBY_H
#define MANAGERLOBBY_H

#include "../PrintMenu.h"
#include "CreateHall.h"
#include "Attributionconcert/AttributionConcert.h"
#include "PrintHall.h"
#include "Attributionconcert/DisplayHallAndConcerts.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void managerlobby()
{

    int choice;
    printf("1: Creer une salle et ses concerts.\n");
    printf("2: Modifier une salle\n");
    printf("3: Consulter les informations d'une salle\n");
    printf("4: Retourner au menu.\n");
    printf("Taper le numero correspondant au choix pour choisir:\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        createhall();
        break;
    case 2:
        attributionconcert();
    case 3:
        printhall();
        break;

    case 4:
        printmenu();
        break;
    default:
        managerlobby();
        break;
    }
}

#endif