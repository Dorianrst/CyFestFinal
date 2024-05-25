#ifndef PRINTHALL_H

#define PRINTHALL_H
#include <stdio.h>
#include <string.h>

#include "../Manager/CreateHall.h"
#include "../PrintMenu.h"
#include "Reserved.h"

void printhall()
{
    Hall hall;
    char hallName[50];
    printf("Veuillez entrer le nom de la salle a afficher:\n");
    scanf("%s", hallName);

    FILE *file = fopen(hallName, "rb"); // ouvrir le fichier en mode lecture binaire
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", hallName);
        return;
    }

    // Lire les informations de la salle
    if (fread(&hall, sizeof(Hall), 1, file) != 1)
    {
        printf("Erreur lors de la lecture du fichier %s\n", hallName);
        fclose(file);
        return;
    }

    // La salle a ete trouvee, imprimer les details
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
        fflush(stdout);
    }

    printf("1:Reserver un place de concert dans une salle?\n ");
    printf("2: Retoruner au menu\n");
    printf("Taper le nméro correspondant au choix\n");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        reservedconcert();
        break;
    case 2:
        printmenu();
        break;
    default:
        printhall();
        break;
    }
    fclose(file);
}

#endif
