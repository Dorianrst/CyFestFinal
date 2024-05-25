#ifndef DELETECONCERT_H
#define DELETECONCERT_H

#include "../CreateHall.h"
#include "../PrintHall.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printmenu();

void deleteconcert()
{
    Hall hall;
    char hallName[50];
    printf("Veuillez entrer le nom de la salle ou le concert doit être supprime:\n");
    scanf("%49s", hallName); // Limit input to prevent buffer overflow

    FILE *file = fopen(hallName, "r+b"); // Open the file in read/write binary mode
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", hallName);
        return;
    }

    printf("Entrez le nom de l'artiste : ");
    char artistName[30];
    fgets(artistName, sizeof(artistName), stdin);
    artistName[strcspn(artistName, "\n")] = 0; // Remove the newline character

    // Search for the hall in the file
    int found = 0;
    while (fread(&hall, sizeof(Hall), 1, file) == 1 && !found)
    {
        if (strcmp(hall.name, hallName) == 0)
        {
            // Hall found, search for the concert
            for (int i = 0; i < hall.numConcerts; i++)
            {
                if (strcmp(hall.time[i].artistName, artistName) == 0)
                {
                    // Concert found, delete it
                    for (int j = i; j < hall.numConcerts - 1; j++)
                    {
                        hall.time[j] = hall.time[j + 1];
                    }
                    hall.numConcerts--;

                    // Rewrite the hall in the file
                    fseek(file, -sizeof(Hall), SEEK_CUR);
                    fwrite(&hall, sizeof(Hall), 1, file);
                    printf("Suppression du concert terminee.\n");
                    found = 1;
                    break;
                }
            }
        }
    }

    if (!found)
    {
        printf("Salle ou concert non trouve.\n");
    }

    fclose(file);
    printf("Voulez-vous retourner au menu (1=oui, 2=Non) ?\n");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printmenu();
        break;
    case 2:
        deleteconcert();
        break;
    default:
        break;
    }
}

#endif