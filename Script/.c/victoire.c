#include "structures.h"
#include <stdio.h>
#include <stdlib.h>

int victoire(JOUEUR team[5])
{
    if (team[1].etat == ALIVE  && team[2].etat == DEAD && team[3].etat == DEAD && team[4].etat == DEAD )             /* Si il reste 1 joueur en vie, il gagne, test pour le joueur 1 */
        return 1;
    else if (team[1].etat == DEAD  && team[2].etat == ALIVE && team[3].etat == DEAD && team[4].etat == DEAD )        /* test pour le joueur 2 */
        return 2;
    else if (team[1].etat == DEAD  && team[2].etat == DEAD && team[3].etat == ALIVE && team[4].etat == DEAD )        /* test pour le joueur 3 */
        return 3;
    else if (team[1].etat == DEAD  && team[2].etat == DEAD && team[3].etat == DEAD && team[4].etat == ALIVE )        /* test pour le joueur 4 */
        return 4;
    else if (team[1].etat == DEAD  && team[2].etat == DEAD && team[3].etat == DEAD && team[4].etat == DEAD )         /* test pour l'égalité */
        return 5;
    else
        return 0;
}
