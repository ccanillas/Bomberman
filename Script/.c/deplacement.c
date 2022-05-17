#include "structures.h"
#include "bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void deplacement_up( CASES carte[LARGEUR][HAUTEUR], JOUEUR team[5], CASES n_joueur )
{                                                                                                    /* Déplacement seulement si le joueur est en vie et qu'il ne s'est pas déplacer depuis 0.15 seconde */

    if ((team[n_joueur].etat) == ALIVE && ((clock() - team[n_joueur].last_input)/CLOCKS_PER_SEC) > TEMPS_DEPLACEMENT   )
    {
        if ( carte[team[n_joueur].position_x][(team[n_joueur].position_y)-1] == GROUND  ||
            carte[team[n_joueur].position_x][(team[n_joueur].position_y)-1] == BONUS  )              /* Vérifie si le joueur peut se deplacer sur la case au dessus */
        {
            if (carte[team[n_joueur].position_x][(team[n_joueur].position_y)-1] == BONUS)            /* Affecte le bonus au joueur si la case du dessus est un bonus*/
                    bonus_effect(team, n_joueur);

            carte[team[n_joueur].position_x][(team[n_joueur].position_y)-1] = n_joueur;              /* Déplace le joueur au dessus*/
            if (carte[team[n_joueur].position_x][(team[n_joueur].position_y)] == n_joueur + 10)      /* Si le joueur est sur une bombe , laisse une bombe derrière lui*/
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = BOMB;
            else
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = GROUND;              /* Autrement on laisse du sol derriere lui*/
            team[n_joueur].position_y=team[n_joueur].position_y-1;                                   /* Actualise la position du joueur dans sa structure*/
            team[n_joueur].last_input = clock();                                                     /* Actualise le temps de dernière input */
        }

        else
            if ( carte[team[n_joueur].position_x][(team[n_joueur].position_y)-1] == EXPLO ||         /* Vérifie si le joueur meurt si il va sur la case du dessus*/
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)-1] == FUME  )
            {
                team[n_joueur].etat = DEAD;                                                          /* Tue le joueur et modifie sa structure*/
            if (carte[team[n_joueur].position_x][(team[n_joueur].position_y)] == n_joueur + 10)
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = BOMB;                /* Si le joueur est sur une bombe , laisse une bombe derrière lui*/
            else
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = GROUND;              /* Remplace l'ancienne position du joueur par du sol*/



            }
    }
}

void deplacement_down( CASES carte[LARGEUR][HAUTEUR], JOUEUR team[4], CASES n_joueur)                /* Même fonction mais pour le bas*/
{
    if ((team[n_joueur].etat) == ALIVE && ((clock() - team[n_joueur].last_input)/CLOCKS_PER_SEC) > TEMPS_DEPLACEMENT   )
    {
        if ( carte[team[n_joueur].position_x][(team[n_joueur].position_y)+1] == GROUND ||
            carte[team[n_joueur].position_x][(team[n_joueur].position_y)+1] == BONUS)
        {
            if (carte[team[n_joueur].position_x][(team[n_joueur].position_y)+1] == BONUS)
                    bonus_effect(team, n_joueur);

            carte[team[n_joueur].position_x][(team[n_joueur].position_y)+1] = n_joueur;
            if (carte[team[n_joueur].position_x][(team[n_joueur].position_y)] == n_joueur + 10)
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = BOMB;
            else
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = GROUND;
            team[n_joueur].position_y=team[n_joueur].position_y+1;
            team[n_joueur].last_input = clock();
        }
        else
            if ( carte[team[n_joueur].position_x][(team[n_joueur].position_y)+1] == EXPLO ||
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)+1] == FUME  )
            {
                 team[n_joueur].etat = DEAD;
            if (carte[team[n_joueur].position_x][(team[n_joueur].position_y)] == n_joueur + 10)
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = BOMB;
            else
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = GROUND;

            }
    }
}



void deplacement_left( CASES carte[LARGEUR][HAUTEUR], JOUEUR team[4], CASES n_joueur)                /* Meme fonction mais pour la gauche*/
{
    if ((team[n_joueur].etat) == ALIVE && ((clock() - team[n_joueur].last_input)/CLOCKS_PER_SEC) > TEMPS_DEPLACEMENT   )
    {
        if ( carte[(team[n_joueur].position_x)-1][team[n_joueur].position_y] == GROUND ||
            carte[(team[n_joueur].position_x)-1][team[n_joueur].position_y] == BONUS)
        {
            if (carte[team[n_joueur].position_x-1][(team[n_joueur].position_y)] == BONUS)
                    bonus_effect(team, n_joueur);
            carte[(team[n_joueur].position_x)-1][team[n_joueur].position_y] = n_joueur;
            if (carte[team[n_joueur].position_x][(team[n_joueur].position_y)] == n_joueur + 10)
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = BOMB;
            else
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = GROUND;
            team[n_joueur].position_x=team[n_joueur].position_x-1;
            team[n_joueur].last_input = clock();
        }
        else
            if ( carte[team[n_joueur].position_x][(team[n_joueur].position_y)+1] == EXPLO ||
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)+1] == FUME  )
            {
                 team[n_joueur].etat = DEAD;
            if (carte[team[n_joueur].position_x][(team[n_joueur].position_y)] == n_joueur + 10)
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = BOMB;
            else
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = GROUND;

            }
    }
}

void deplacement_right( CASES carte[LARGEUR][HAUTEUR], JOUEUR team[4], CASES n_joueur)               /* Meme fonction mais pour la droite */
{
    if ((team[n_joueur].etat) == ALIVE && ((clock() - team[n_joueur].last_input)/CLOCKS_PER_SEC) > TEMPS_DEPLACEMENT   )
    {
        if ( carte[(team[n_joueur].position_x)+1][team[n_joueur].position_y] == GROUND ||
            carte[(team[n_joueur].position_x)+1][team[n_joueur].position_y] == BONUS )
        {
            if (carte[(team[n_joueur].position_x)+1][team[n_joueur].position_y] == BONUS)
                bonus_effect(team, n_joueur);
            carte[(team[n_joueur].position_x)+1][team[n_joueur].position_y] = n_joueur;
            if (carte[team[n_joueur].position_x][(team[n_joueur].position_y)] == n_joueur + 10)
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = BOMB;
            else
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = GROUND;
            team[n_joueur].position_x=team[n_joueur].position_x+1;
            team[n_joueur].last_input = clock();
        }
        else
            if ( carte[team[n_joueur].position_x][(team[n_joueur].position_y)+1] == EXPLO ||
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)+1] == FUME  )
            {
                 team[n_joueur].etat = DEAD;
            if (carte[team[n_joueur].position_x][(team[n_joueur].position_y)] == n_joueur + 10)
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = BOMB;
            else
                carte[team[n_joueur].position_x][(team[n_joueur].position_y)] = GROUND;

            }
    }
}
