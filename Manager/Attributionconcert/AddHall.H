#ifndef ADDHALL_H
#define ADDHALL_H

#include "../../PrintMenu.h"
#include "../CreateHall.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addhall()
{
    FILE *file = fopen("halls.dat", "rb+");
    if (file == NULL)
    {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    char hallName[30];
    printf("Entrez le nom de la salle ou vous voulez ajouter le concert :\n");
    scanf("%29s", hallName);

    Hall hall;
    int hallFound = 0;
    while (fread(&hall, sizeof(Hall), 1, file) == 1)
    {
        if (strcmp(hall.name, hallName) == 0)
        {
            hallFound = 1;
            break;
        }
    }

    if (!hallFound)
    {
        printf("Salle non trouvee.\n");
        fclose(file);
        return;
    }

    int numConcerts;
    printf("Combien de concerts voulez-vous ajouter?\n");
    scanf("%d", &numConcerts);

    if (numConcerts > HOURS - hall.numConcerts)
    {
        printf("Pas assez de creneaux disponibles.\n");
        fclose(file);
        return;
    }

    for (int j = 0; j < numConcerts; j++)
    {
        Artist newConcert;
        printf("Entrez les details du concert %d :\n", j + 1);
        printf("Entrez le nom de l'artiste :\n");
        scanf("%29s", newConcert.artistName);
        printf("Entrez l'heure de debut du concert :\n");
        scanf("%d", &newConcert.startConcert);
        printf("Entrez l'heure de fin du concert :\n");
        scanf("%d", &newConcert.endConcert);

        for (int i = 0; i < hall.numConcerts; i++)
        {
            if ((hall.time[i].startConcert < newConcert.endConcert) && (newConcert.startConcert < hall.time[i].endConcert))
            {
                printf("Conflit d'horaire avec un autre concert.\n");
                fclose(file);
                return;
            }
        }

        hall.time[hall.numConcerts] = newConcert;
        hall.numConcerts++;
    }

    fseek(file, -sizeof(Hall), SEEK_CUR);
    fwrite(&hall, sizeof(Hall), 1, file);
    fclose(file);

    printf("Ajout des concerts a la salle termine.\n");
    printf("Voulez-vous retourner au menu (1=oui, 2=non) ?\n");
    int choice;
    scanf("%d", &choice);

    if (choice == 1)
    {
        printmenu();
    }
    else
    {
        addhall();
    }
}

#endif
