#ifndef CREATEHALL_H
#define CREATEHALL_H

#include "../PrintMenu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printmenu(void);

#define MAXCATEGORIE 4
#define HOURS 24
#define MAX_HALL 5

typedef struct
{
    char artistName[30];
    int startConcert;
    int endConcert;
} Artist;

typedef struct
{
    char name[30];
    int row;
    int setPerRow;
    char seatCategorie[MAXCATEGORIE][30];
    int price[MAXCATEGORIE];
    int startRow[MAXCATEGORIE];
    int endRow[MAXCATEGORIE];
    int pit;
    int NameCate[MAXCATEGORIE];
    char *sieges;
    char etat;
    Artist time[HOURS]; // Utilisation d'un tableau de structures Artist
    int numConcerts;
} Hall;

Hall tabHall[MAX_HALL];
int NumberHall;
int sizetab;
int NumbCat;

void createhall()
{
    system("cls");
    printf("Combien de salles voulez-vous creer ?\n");
    scanf("%d", &NumberHall);
    getchar();

    for (int i = 0; i < NumberHall; i++)
    {
        Hall hall;

        printf("Informations de la salle %d\n", i + 1);

        printf("Quel est le nom de la salle ? ");
        fgets(hall.name, sizeof(hall.name), stdin);
        hall.name[strcspn(hall.name, "\n")] = '\0';

        printf("Quel est le nombre de rangees ? ");
        scanf("%d", &hall.row);
        getchar();

        printf("Quel est le nombre de sièges par rangee ? ");
        scanf("%d", &hall.setPerRow);
        getchar();

        printf("Entrer le nombre de categories disponibles : ");
        scanf("%d", &NumbCat);
        getchar();

        for (int j = 0; j < NumbCat; j++)
        {
            printf("Entrer le nom de la categorie %d : ", j + 1);
            fgets(hall.seatCategorie[j], sizeof(hall.seatCategorie[j]), stdin);
            hall.seatCategorie[j][strcspn(hall.seatCategorie[j], "\n")] = '\0';

            printf("Entrer le prix de la categorie %d : ", j + 1);
            scanf("%d", &hall.price[j]);
            getchar();

            printf("Entrer la rangee de debut pour la categorie %d : ", j + 1);
            scanf("%d", &hall.startRow[j]);
            getchar();

            printf("Entrer la rangee de fin pour la categorie %d : ", j + 1);
            scanf("%d", &hall.endRow[j]);
            getchar();
        }

        printf("Y a-t-il une fosse (1=oui, 0=non) : ");
        scanf("%d", &hall.pit);
        getchar();

        if (hall.pit == 1)
        {
            hall.setPerRow *= 2;
        }

        hall.sieges = (char *)malloc(hall.row * hall.setPerRow * sizeof(char));
        if (hall.sieges == NULL)
        {
            printf("Erreur d'allocation de memoire pour les sièges.\n");
            return;
        }

        for (int r = 0; r < hall.row; r++)
        {
            for (int j = 0; j < hall.setPerRow; j++)
            {
                for (int c = 0; c < NumbCat; c++)
                {
                    if (r >= hall.startRow[c] && r <= hall.endRow[c])
                    {
                        hall.sieges[r * hall.setPerRow + j] = hall.price[c];
                        break;
                    }
                }
            }
        }

        for (int j = 0; j < HOURS; j++)
        {
            strcpy(hall.time[j].artistName, "Libre");
            hall.time[j].startConcert = -1;
            hall.time[j].endConcert = -1;
        }

        int numberOfConcerts;
        printf("Combien de concerts voulez-vous dans la salle ? ");
        scanf("%d", &numberOfConcerts);
        getchar();

        hall.numConcerts = numberOfConcerts;

        for (int n = 0; n < numberOfConcerts; n++)
        {
            int start, end;
            printf("Entrer l'heure de debut du concert %d (0-23) : ", n + 1);
            scanf("%d", &start);
            printf("Entrer l'heure de fin du concert %d (1-24) : ", n + 1);
            scanf("%d", &end);
            getchar();

            if (start < 0 || start >= HOURS || end <= start || end > HOURS)
            {
                printf("Erreur: heures de concert invalides.\n");
                return;
            }

            for (int j = start; j < end; j++)
            {
                hall.time[j].startConcert = start;
                hall.time[j].endConcert = end;
            }

            printf("Entrer le nom de l'artiste qui joue de %d h à %d h : ", start, end);
            fgets(hall.time[start].artistName, sizeof(hall.time[start].artistName), stdin);
            hall.time[start].artistName[strcspn(hall.time[start].artistName, "\n")] = '\0';

            for (int j = start + 1; j < end; j++)
            {
                strcpy(hall.time[j].artistName, hall.time[start].artistName);
            }
        }

        FILE *file = fopen(hall.name, "wb");
        if (file == NULL)
        {
            printf("Erreur d'ouverture du fichier pour sauvegarde.\n");
            return;
        }
        fwrite(&hall, sizeof(Hall), 1, file);

        fclose(file);
        free(hall.sieges);
        tabHall[i] = hall;
    }
    sizetab = NumberHall;
    printf("Creation des salles terminee.\n");
    printmenu();
}

#endif
