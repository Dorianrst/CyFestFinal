#ifndef DISPLAYHALLANDCONCERT_H
#define DISPLAYHALLANDCONCERT_H

#include "../CreateHall.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayhallandconcerts()
{
    FILE *file = fopen("halls.dat", "rb");
    if (file == NULL)
    {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    Hall hall;
    Artist *time = (Artist *)malloc(HOURS * sizeof(Artist));
    if (time == NULL)
    {
        printf("Erreur d'allocation de memoire.\n");
        fclose(file);
        return;
    }

    fread(&hall, sizeof(Hall), 1, file);
    fread(time, sizeof(Artist), HOURS, file);

    // Affichez les informations sur 'hall' et 'time' ici

    fclose(file);
    free(time);
}

#endif