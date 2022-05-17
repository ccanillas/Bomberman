/* Fichier déplacement.h

Usage : comporte tous les prototypes des déplacements

Projet Bomberman 1A

*/

#ifndef DEPLACEMENT_H_INCLUDED
#define DEPLACEMENT_H_INCLUDED

#include "structures.h"


void deplacement_up( CASES carte[LARGEUR][HAUTEUR], JOUEUR team[5], CASES n_joueur);
void deplacement_down( CASES carte[LARGEUR][HAUTEUR], JOUEUR team[5], CASES n_joueur);
void deplacement_left( CASES carte[LARGEUR][HAUTEUR], JOUEUR team[5], CASES n_joueur);
void deplacement_right( CASES carte[LARGEUR][HAUTEUR], JOUEUR team[5], CASES n_joueur);


#endif // DEPLACEMENT_H_INCLUDED
