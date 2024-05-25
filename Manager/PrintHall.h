#ifndef PRINTHALL_H
#define PRINTHALL_H

#include <stdio.h>
#include <string.h>

#include "CreateHall.h"
#include "../PrintMenu.h"

void printmenu(); // Assuming this is declared elsewhere
void printfinal(void);
void printhall()
{
    Hall hall;
    char hallName[50];
    printf("Veuillez entrer le nom de la salle a afficher:\n");
    scanf("%49s", hallName); // Limit input to prevent buffer overflow
    FILE *file = fopen(hallName, "r");
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", hallName);
        return;
    }

    int found = 0;
    while (fread(&hall, sizeof(Hall), 1, file))
    {
        if (strcmp(hall.name, hallName) == 0)
        {
            found = 1;
            printf("Nom de la salle : %s\n", hall.name);
            printf("Nombre de rangees : %d\n", hall.row);
            printf("Nombre de sieges par rangee : %d\n", hall.setPerRow);
            printf("Categories : ");
            for (int i = 0; i < MAXCATEGORIE; i++)
            {
                printf("%s ", hall.seatCategorie[i]);
            }
            printf("\n");
            printf("Nombre de concerts : %d\n", hall.numConcerts);
            for (int i = 0; i < hall.numConcerts; i++)
            {
                printf("Concert %d :\n", i + 1);
                printf("  Artiste : %s\n", hall.time[i].artistName);
                printf("  Heure de debut : %d\n", hall.time[i].startConcert);
                printf("  Heure de fin : %d\n", hall.time[i].endConcert);
            }
            break;
        }
    }
    fclose(file);

    if (!found)
    {
        printf("Salle non trouvee.\n");
    }

    printf("Voulez vous retourner au menu(1=oui,2=Non)\n");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printmenu();
        break;
    case 2:
        printfinal();
        break;
    default:
        return;
    }
}

#endif