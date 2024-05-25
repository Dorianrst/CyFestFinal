#ifndef PRINTFINAL_H
#define PRINTFINAL_H

#include <stdio.h>
#include <string.h>

#include "../Manager/CreateHall.h"
#include "../PrintMenu.h"
#include "Reserved.h"

void printfinal()
{
    FILE *file;
    char hallName[100];
    char line[1024];
    char filename[100];

    printf("Veuillez entrer le nom de la salle a afficher:\n");
    scanf("%s", hallName);
    getchar(); // To consume the newline character left by scanf

    // Add .txt extension to hallName
    snprintf(filename, sizeof(filename), "%s.txt", hallName);

    printf("Trying to open file: %s\n", filename); // Debugging print

    file = fopen(filename, "r"); // Open the file in text mode
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        return;
    }

    // Read and print the file contents line by line
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }
    fclose(file);

    printf("1: Reserver un place de concert dans une salle?\n");
    printf("2: Retourner au menu\n");
    printf("Tapez le numéro correspondant au choix\n");

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
        printfinal();
        break;
    }
}

#endif
