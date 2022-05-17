/* Fichier initialisation.c

Usage : fonctions d'initialisation

Projet Bomberman 1A

*/

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"



void initialisation_map(CASES carte[LARGEUR][HAUTEUR])  /* Création de la carte */
{
    int l,h;                                            /* On crée deux variables hauteur h et largeur l */

    for (l = 0; l < LARGEUR; l++)                       /* Première ligne de la map -> que des murs */
        carte[l][0] = WALL;

    for (h = 1; h < HAUTEUR-1; h++)                     /* De la 2e à l'avant dernière ligne : */
    {                                                   /* Une ligne sur deux est remplie de case "caisse", tandis que les autres sont */
        carte[0][h] = WALL;                             /* remplies avec un mur, puis une caisse, un mur, une caisse, un mur... jusqu'à */
        for (l = 1; l < LARGEUR-1; l++)                 /* atteindre le bord de la map qui se fini par un mur */
        {
            if (h % 2 == 1)
                carte [l][h] = BOX;
            else
            {
                if (l % 2 == 1)
                    carte[l][h] = BOX;
                else
                    carte[l][h] = WALL;
            }
        }
        carte[LARGEUR-1][h] = WALL;
    }

    for (l = 0; l < LARGEUR; l++)
        carte [l][HAUTEUR-1] = WALL;


}

void initialisation_joueur(JOUEUR team[],CASES carte[LARGEUR][HAUTEUR]) /* Mise en place des joueurs et du minimum d'espace autour d'eux */
{
    int i;

    for (i = 1; i < 5; i++)
    {
        team[i].last_input = 0;
        team[i].etat = ALIVE;                                           /* Initialisation des joueurs -> on les remet en vie */
        switch (i)
        {
            case 1 :
                team[i].position_x = 1;                                 /* Chaque joueur est initialisé de la même manière : */
                team[i].position_y = 1;                                 /* On place le joueur X dans un coin prédéfini de la map */
                carte[1][1] = P1;                                       /* en remplaçant les deux caisses adjacentes par du sol */
                carte[2][1] = GROUND;                                   /* pour qu'il puisse poser une bombe de manière safe et */
                carte[1][2] = GROUND;                                   /* commencer à progresser */
                break;
            case 2 :
                team[i].position_x = 1;
                team[i].position_y = HAUTEUR-2;
                carte[1][HAUTEUR - 2] = P2;
                carte[1][HAUTEUR - 3] = GROUND;
                carte[2][HAUTEUR - 2] = GROUND;
                break;
            case 3 :
                team[i].position_x = LARGEUR-2 ;
                team[i].position_y = 1;
                carte[LARGEUR - 2][1] = P3;
                carte[LARGEUR - 3][1] = GROUND;
                carte[LARGEUR - 2][2] = GROUND;
                break;
            case 4 :
                team[i].position_x = LARGEUR-2;
                team[i].position_y = HAUTEUR-2;
                carte[LARGEUR - 2][HAUTEUR - 2] = P4;
                carte[LARGEUR - 3][HAUTEUR - 2] = GROUND;
                carte[LARGEUR - 2][HAUTEUR - 3] = GROUND;
                break;
        }
        team[i].nb_bombe = INIT_NB_BOMBE;                               /* On initialise le nombre de bombes posables par chaque joueur à 1 */
        team[i].taille_bombe = INIT_TAILLE_BOMBE;                       /* ainsi que la taille des explosions à 1 case par côté et le nombre */
        team[i].nb_bombe_actif = 0;                                     /* de bombes posées à 0 pour éviter que des parties qui s'enchaîne ne */
    }                                                                   /* limite le nombre possible de bombe à poser (voire empêche d'en poser) */
}

void initialisation_bombes_explosions(BOMBE all_bombs[], EXPLOSION all_explo[]) /* Initialisation des tableaux de bombes et explosions */
{
    int i;

    for(i = 0; i < TAILLE_TAB_EXPLO; ++i)                                            /* Du fait du fonctionnement des bombes et explosions, il est */
    {                                                                   /* nécessaire d'initialiser les deux tableaux recensant les bombes */
        if (i < TAILLE_TAB_BOMB)                                                     /* et explosions actives en les remplissant de bombes et explosions */
        {                                                               /* "mortes", qui seront remise en vie dès lors qu'on aura besoin de */
            all_bombs[i].etat = DEAD;                                   /* d'en faire apparaître une */
            all_bombs[i].tspawn = -1.0;
        }
        all_explo[i].etat = DEAD;
        all_explo[i].tspawn = -1.0;
    }
}





