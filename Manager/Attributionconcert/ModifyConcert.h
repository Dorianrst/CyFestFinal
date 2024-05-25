#ifndef MODIFYCONCERT_H
#define MODIFYCONCERT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../CreateHall.h"
#include "../../PrintMenu.h"

void modifyhall()
{
    Hall hall;
    char hallName[50];
    printf("Veuillez entrer le nom de la salle a modifier:\n");
    scanf("%s", hallName);

    FILE *file = fopen(hallName, "r+"); // open the file in read/write mode
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", hallName);
        return;
    }

    printf("Qu'est-ce que vous voulez modifier ?\n");
    printf("1: Le nom\n2: Les categories\n3: Les rangees\n4: Les sieges par rangee\n5: Les noms d'artistes\n6: Les horaires des artistes\n");
    int choice;
    scanf("%d", &choice);

    // Search for the hall in the file
    while (fread(&hall, sizeof(Hall), 1, file) == 1)
    {
        if (strcmp(hall.name, hallName) == 0)
        {
            // The hall has been found, modify it
            switch (choice)
            {
            case 1:
                printf("Entrez le nouveau nom de la salle : ");
                scanf("%s", hall.name);
                break;
            case 2:
                printf("Entrez les nouvelles categories (separees par des espaces) : ");
                for (int i = 0; i < MAXCATEGORIE; i++)
                {
                    scanf("%s", hall.seatCategorie[i]);
                }
                break;
            case 3:
                printf("Entrez le nouveau nombre de rangees : ");
                scanf("%d", &hall.row);
                break;
            case 4:
                printf("Entrez le nouveau nombre de sieges par rangee : ");
                scanf("%d", &hall.setPerRow);
                break;
            case 5:
                printf("Entrez les nouveaux noms d'artistes (separes par des espaces) : ");
                for (int i = 0; i < hall.numConcerts; i++)
                {
                    scanf("%s", hall.time[i].artistName);
                }
                break;
            case 6:
                printf("Entrez les nouveaux horaires des artistes (separes par des espaces) : ");
                for (int i = 0; i < hall.numConcerts; i++)
                {
                    printf("Artiste %d, heure de debut : ", i + 1);
                    scanf("%d", &hall.time[i].startConcert);
                    printf("Artiste %d, heure de fin : ", i + 1);
                    scanf("%d", &hall.time[i].endConcert);
                }
                break;
            }

            // Rewrite the hall in the file
            fseek(file, -sizeof(Hall), SEEK_CUR);
            fwrite(&hall, sizeof(Hall), 1, file);

            printf("Modification de la salle terminee.\n");
            fclose(file);
            printf("Voulez vous retourner au menu(1=oui,2=Non)\n");
            int choice;
            switch (choice)
            {
            case 1:
                printmenu();
                break;
            case 2:
                modifyhall();
                break;
            default:
                return;
                break;
            }
        }
    }
    fclose(file);
    printf("Salle non trouvee.\n");
}
#endif