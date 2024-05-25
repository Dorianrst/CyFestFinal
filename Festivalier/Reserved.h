#ifndef RESERVERDHALL_H
#define RESERVERDHALL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../PrintMenu.h"
#include "../Manager/CreateHall.h"

void reservedconcert()
{
    char hallName[50];
    printf("Veuillez entrer le nom de la salle où vous voulez reserver un concert:\n");
    scanf("%49s", hallName);

    Hall hall;
    FILE *file = fopen(hallName, "rb");
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", hallName);
        printmenu();
        return;
    }

    if (fread(&hall, sizeof(Hall), 1, file) != 1)
    {
        printf("Erreur de lecture des informations de la salle.\n");
        fclose(file);
        return;
    }

    printf("Nom de la salle : %s\n", hall.name);
    printf("Nombre de concerts : %d\n", hall.numConcerts);

    for (int i = 0; i < hall.numConcerts; i++)
    {
        printf("Concert %d :\n", i + 1);
        printf("  Artiste : %s\n", hall.time[i].artistName);
        printf("  Heure de debut : %d\n", hall.time[i].startConcert);
        printf("  Heure de fin : %d\n", hall.time[i].endConcert);
    }

    printf("Voulez vous reserver un concert (1=oui,2=Non)\n");
    int choice;
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Quel concert voulez-vous reserver ? (Entrez le numero du concert)\n");
        int concertChoice;
        scanf("%d", &concertChoice);

        if (concertChoice > 0 && concertChoice <= hall.numConcerts)
        {
            printf("Vous avez reserve le concert %d :\n", concertChoice);
            printf("  Artiste : %s\n", hall.time[concertChoice - 1].artistName);
            printf("  Heure de debut : %d\n", hall.time[concertChoice - 1].startConcert);
            printf("  Heure de fin : %d\n", hall.time[concertChoice - 1].endConcert);

            printf("Voici la disposition des sieges :\n");

            int numSpaces = (72 - strlen("Scene")) / 2;

            for (int i = 0; i < numSpaces; i++)
            {
                printf(" ");
            }

            printf("Scene\n");
            printf("-------------------------------------------------------------------------\n");
            int numSpacesSeats = (72 - (hall.setPerRow * 2)) / 2;

            for (int r = 0; r < hall.row; r++)
            {
                for (int i = 0; i < numSpacesSeats; i++)
                {
                    printf(" ");
                }

                for (int s = 0; s < hall.setPerRow; s++)
                {
                    printf("\x1b[32mL \x1b[0m"); // L en vert
                }
                printf("\n");
            }

            printf("Legende :\n");
            printf("  Categorie A : 50 euros\n");
            printf("  Categorie B : 30 euros\n");
            printf("  Categorie C : 20 euros\n");

            printf("Combien de sieges voulez-vous reserver ?\n");
            int numSeats;
            scanf("%d", &numSeats);

            for (int i = 0; i < numSeats; i++)
            {
                printf("Veuillez entrer le numero de la rangee pour le siege %d:\n", i + 1);
                int row;
                scanf("%d", &row);

                printf("Veuillez entrer le numero du siege dans la rangee pour le siege %d:\n", i + 1);
                int seat;
                scanf("%d", &seat);

                if (hall.sieges[(row - 1) * hall.setPerRow + (seat - 1)] == '1')
                {
                    hall.sieges[(row - 1) * hall.setPerRow + (seat - 1)] = '0';
                    printf("Vous avez reserve le siege %d dans la rangee %d.\n", seat, row);
                }
                else
                {
                    printf("Desole, le siege %d dans la rangee %d est deja reserve.\n", seat, row);
                    i--; // Ask for the seat again
                }
            }
        }
        else
        {
            printf("Choix de concert invalide.\n");
        }

        fclose(file);
    }
    else
    {
        fclose(file);
    }
}

#endif
