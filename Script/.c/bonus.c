/* Fichier bonus.c

Usage : fonctions des bonus

Projet Bomberman 1A

*/

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
int rand_a_b(int a, int b)                                      /* Fonction g�n�rant un nombre al�atoire allant appartenant � [a , b-1] */
{
    return rand()%(b-a) +a;
}

void spawn_bonus(CASES carte [LARGEUR][HAUTEUR],int x, int y)   /* Apparition d'un bonus */
{
    int proba = 0;                                              /* On cr�e une variable de probabilit� */

    proba = rand_a_b(0, 11);                                    /* On lui assigne une valeur al�atoire entre 0 et 10 */

    if (proba < 5)                                              /* On fait appara�tre un bonus avec 40% de chance suivant la valeur de proba */
        carte[x][y] = BONUS;
    else
        carte[x][y] = GROUND;

}

void bonus_effect(JOUEUR team[], int n_joueur)                  /* Quel effet aura ce bonus ? */
{
    int proba = 0;

    proba = rand_a_b(1, 101);                                   /* On assigne � proba une valeur entre 0 et 100 */

    if (proba > 0 && proba <= 60)                               /* Bonus : Taille de bombe +1 -> 60% de chance */
    {
        if (team[n_joueur].taille_bombe < TAILLE_EXPLO_MAX)     /* Ne marche qu'� condition que la maximum n'est pas atteint */
            team[n_joueur].taille_bombe++;
    }
    else if (proba > 60 && proba <= 100)                        /* Bonus : Nombre de bombes posables +1 -> 40% de chance */
    {
        if (team[n_joueur].nb_bombe < NB_BOMBES_MAX)            /* M�me principe que ci-dessus */
            team[n_joueur].nb_bombe++;
    }
}
