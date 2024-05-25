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

    FILE *file = fopen(hallName, "r");
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", hallName);
        printmenu();
        return;
    }

    Hall hall;
    char line[1024];

    // Read hall data from file
    fgets(line, 1024, file);
    sscanf(line, "Name: %s\n", hall.name);

    fgets(line, 1024, file);
    sscanf(line, "Row: %d\n", &hall.row);

    fgets(line, 1024, file);
    sscanf(line, "Set per row: %d\n", &hall.setPerRow);

    fgets(line, 1024, file);
    sscanf(line, "Number of categories: %d\n", &NumbCat);

    for (int j = 0; j < NumbCat; j++)
    {
        fgets(line, 1024, file);
        sscanf(line, "Category %d: %s, Price: %d, Start row: %d, End row: %d\n",
               &j, hall.seatCategorie[j], &hall.price[j], &hall.startRow[j], &hall.endRow[j]);
    }

    fgets(line, 1024, file);
    sscanf(line, "Pit: %d\n", &hall.pit);

    for (int r = 0; r < hall.row; r++)
    {
        fgets(line, 1024, file);
        for (int j = 0; j < hall.setPerRow; j++)
        {
            hall.sieges[r * hall.setPerRow + j] = line[j];
        }
    }

    fgets(line, 1024, file);
    sscanf(line, "Number of concerts: %d\n", &hall.numConcerts);

    for (int n = 0; n < hall.numConcerts; n++)
    {
        fgets(line, 1024, file);
        sscanf(line, "Concert %d: Start: %d, End: %d, Artist: %s\n",
               &n, &hall.time[n].startConcert, &hall.time[n].endConcert, hall.time[n].artistName);
    }

    //... rest of the code...

    // Write updated hall data to file
    file = fopen(hallName, "w");
    if (file == NULL)
    {
        printf("Erreur d'ouverture du fichier pour sauvegarde.\n");
        return;
    }

    fprintf(file, "Name: %s\n", hall.name);
    fprintf(file, "Row: %d\n", hall.row);
    fprintf(file, "Set per row: %d\n", hall.setPerRow);
    fprintf(file, "Number of categories: %d\n", NumbCat);

    for (int j = 0; j < NumbCat; j++)
    {
        fprintf(file, "Category %d: %s, Price: %d, Start row: %d, End row: %d\n",
                j + 1, hall.seatCategorie[j], hall.price[j], hall.startRow[j], hall.endRow[j]);
    }

    fprintf(file, "Pit: %d\n", hall.pit);

    for (int r = 0; r < hall.row; r++)
    {
        for (int j = 0; j < hall.setPerRow; j++)
        {
            fprintf(file, "%c", hall.sieges[r * hall.setPerRow + j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "Number of concerts: %d\n", hall.numConcerts);

    for (int n = 0; n < hall.numConcerts; n++)
    {
        fprintf(file, "Concert %d: Start: %d, End: %d, Artist: %s\n",
                n + 1, hall.time[n].startConcert, hall.time[n].endConcert, hall.time[n].artistName);
    }

    fclose(file);
}

#endif
