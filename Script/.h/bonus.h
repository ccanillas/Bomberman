/* Fichier bonus.h

Usage : prototypes des fct° liées aux bonus

Projet Bomberman 1A

*/

#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include "structures.h"

void spawn_bonus  (CASES carte[LARGEUR][HAUTEUR], int x, int y);
void bonus_effect (JOUEUR team[], int n_joueur);

#endif // BONUS_H_INCLUDED
