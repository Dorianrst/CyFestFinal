#ifndef ATTRIBUTIONCONCERT_H
#define ATTRIBUTIONCONCERT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../PrintMenu.h"
#include "AddHall.H"
#include "DisplayHallAndConcerts.h"
#include "DeleteConcert.h"
#include "ModifyConcert.h"

void attributionconcert()
{
    displayhallandconcerts();

    printf("Que voulez-vous faire ?\n");
    printf("1: Ajouter un concert\n");
    printf("2: Supprimer un concert\n");
    printf("3: Modifier un concert\n");
    printf("4:Retourner au menu");
    printf("Tapez le chiffre correspondant à l'option pour choisir\n");

    int option;
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        addhall();
        break;
    case 2:
        deleteconcert();
        break;
    case 3:
        modifyhall();
        break;
    case 4:
        printmenu();
        break;
    default:
        printf("Option non valide.\n");
        attributionconcert();
        break;
    }
}

#endif