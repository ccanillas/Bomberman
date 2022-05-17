/* Fichier bonus.h

Usage : prototypes des fct° liées aux bombes et explosions

Projet Bomberman 1A

*/

#ifndef BOMBE_H_INCLUDED
#define BOMBE_H_INCLUDED

#include "structures.h"

void pose_bombe(CASES carte[LARGEUR][HAUTEUR], BOMBE all_bombs[], JOUEUR team[], int n_joueur);

void pose_explo(EXPLOSION all_explo[], int x, int y);

void explose_bombe(CASES carte[LARGEUR][HAUTEUR], BOMBE all_bombs[], int n_bombe, JOUEUR team[], EXPLOSION all_explo[]);

void remove_explo(CASES carte[LARGEUR][HAUTEUR], EXPLOSION all_explo[], int n_explo);

int time_checker (CASES carte[LARGEUR][HAUTEUR], BOMBE all_bombs[], EXPLOSION all_explo[], JOUEUR team[]);

#endif // BOMBE_H_INCLUDED
