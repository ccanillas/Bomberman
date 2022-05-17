/* Fichier initialisation.h

Usage : prototypes des fonctions d'initialisation

Projet Bomberman 1A

*/

#ifndef INITIALISATION_H_INCLUDED
#define INITIALISATION_H_INCLUDED

#include "structures.h"

void initialisation_map (CASES carte[LARGEUR][HAUTEUR]);

void initialisation_joueur(JOUEUR team[],CASES carte[LARGEUR][HAUTEUR]);

void initialisation_bombes_explosions(BOMBE all_bombs[], EXPLOSION all_explo[]);

#endif // INITIALISATION_H_INCLUDED
