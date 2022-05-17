/* Fichier affichage.h

Usage : comporte les prototypes de l'affichage

Projet Bomberman 1A

*/

#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

#include "structures.h"
#include "SDL.h"

void affichage_jeu(CASES tab[LARGEUR][HAUTEUR], SDL_Surface* ecran, SDL_Surface* I_Ground, SDL_Surface* I_P1, SDL_Surface* I_P2, SDL_Surface* I_P3, SDL_Surface* I_P4, SDL_Surface* I_Bomb, SDL_Surface* I_Explo, SDL_Surface* I_Fume, SDL_Surface* I_Box, SDL_Surface* I_Bonus, SDL_Surface* I_Wall, SDL_Surface* I_P1Bomb, SDL_Surface* I_P2Bomb, SDL_Surface* I_P3Bomb, SDL_Surface* I_P4Bomb);
void affichage_interface(SDL_Surface *ecran, JOUEUR team[5], SDL_Surface *I_interface_bomb, SDL_Surface *I_interface_explo1, SDL_Surface *I_interface_explo2, SDL_Surface *I_interface_explo3, SDL_Surface *I_interface_explo4, SDL_Surface *I_interface_explo5, SDL_Surface *I_interface_explo6, SDL_Surface *I_interface_P1, SDL_Surface *I_interface_P2, SDL_Surface *I_interface_P3, SDL_Surface *I_interface_P4, SDL_Surface *I_interface_dead);
void affichage_menu(SDL_Surface *ecran, MENU image_menu, SDL_Surface *I_menu_jouer, SDL_Surface *I_menu_credit, SDL_Surface *I_menu_quitter);
void credit(SDL_Surface *ecran);
void affichage_victoire(int n_joueur, SDL_Surface *ecran);

#endif
