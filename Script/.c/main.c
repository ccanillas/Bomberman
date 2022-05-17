/* Fichier main.c

Usage : fichier test

Projet Bomberman 1A

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "initialisation.h"
#include "deplacement.h"
#include "Bombe.h"

void tempo()
{
    clock_t temps = clock();

    while ((clock()/CLOCKS_PER_SEC) - (temps/CLOCKS_PER_SEC) < 0.1)
    {

    }
}

void afficher(CASES carte[LARGEUR][HAUTEUR])
{
    int h,l;

    system("cls");

    for(h=0; h<HAUTEUR; ++h)
    {
        printf("\n");
        for(l=0; l<LARGEUR; ++l)
        {
            printf("%i ",carte[l][h]);

        }
    }


}

void main()
{
    int i;

    CASES carte[LARGEUR][HAUTEUR];
    JOUEUR team[5];
    BOMBE all_bombs[40];
    EXPLOSION all_explo[400];
    clock_t temps;

    initialisation_map(carte);

    initialisation_joueur(team, carte);

    initialisation_bombes_explosions(all_bombs, all_explo);

    afficher(carte);
    printf("\n\n");
    system("PAUSE");

    deplacement_right(carte, team, 1);
    afficher(carte);
    tempo();

    pose_bombe(carte, all_bombs, team, 1);
    afficher(carte);
    tempo();

    deplacement_left(carte, team, 1);
    pose_bombe(carte, all_bombs, team, 1);
    afficher(carte);
    tempo();

    deplacement_down(carte, team, 1);
    afficher(carte);
    tempo();


    temps = clock();

    while ((clock()/CLOCKS_PER_SEC) - (temps/CLOCKS_PER_SEC) < 5)
    {
        time_checker(carte, all_bombs, all_explo, team);
        afficher(carte);
    }

    pose_bombe(carte, all_bombs, team, 1);
    afficher(carte);
    tempo();

    deplacement_up(carte, team, 1);
    afficher(carte);
    tempo();

    deplacement_right(carte, team, 1);
    afficher(carte);
    tempo();

    deplacement_right(carte, team, 1);
    afficher(carte);
    tempo();

    temps = clock();

    while ((clock()/CLOCKS_PER_SEC) - (temps/CLOCKS_PER_SEC) < 5)
    {
        time_checker(carte, all_bombs, all_explo, team);
        afficher(carte);
    }

    pose_bombe(carte, all_bombs, team, 1);
    afficher(carte);
    tempo();

    deplacement_left(carte, team, 1);
    afficher(carte);
    tempo();

    deplacement_left(carte, team, 1);
    afficher(carte);
    tempo();

    deplacement_down(carte, team, 1);
    afficher(carte);
    tempo();

    temps = clock();

    while ((clock()/CLOCKS_PER_SEC) - (temps/CLOCKS_PER_SEC) < 5)
    {
        time_checker(carte, all_bombs, all_explo, team);
        afficher(carte);
    }


}
