#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include <SDL.h>

void affichage_jeu(CASES tab[LARGEUR][HAUTEUR], SDL_Surface* ecran, SDL_Surface* I_Ground, SDL_Surface* I_P1, SDL_Surface* I_P2, SDL_Surface* I_P3, SDL_Surface* I_P4, SDL_Surface* I_Bomb, SDL_Surface* I_Explo, SDL_Surface* I_Fume, SDL_Surface* I_Box, SDL_Surface* I_Bonus, SDL_Surface* I_Wall, SDL_Surface* I_P1Bomb, SDL_Surface* I_P2Bomb, SDL_Surface* I_P3Bomb, SDL_Surface* I_P4Bomb)
{

    /* Affichage de la carte case par case grâce au tableau de la map */
    /* Les images sont chargées préalablement dans la fonction jeu pour éviter qu'elles soient */
    /* chargées à chaque itération de la boucle de jeu et ainsi diminuer la consommation de ressources */


    int l, h;

    /* initialise la position de la première image */
    SDL_Rect positiontab;

    positiontab.x = 385;
    positiontab.y = 139;



    for(h = 0; h < 13; h++) /* Boucle pour afficher ligne par ligne */
    {
        for(l = 0; l < 15; l++) /* Boucle pour afficher case par case */
        {
            switch(tab[l][h]) /* Switch pour afficher la bonne image en fonction de la valeur de la case */
            {
                case WALL:
                SDL_BlitSurface(I_Wall, NULL, ecran, &positiontab);  /* Colle une image sur l'écran */
                break;

                case GROUND:
                SDL_BlitSurface(I_Ground, NULL, ecran, &positiontab);
                break;

                case P1:
                SDL_BlitSurface(I_P1, NULL, ecran, &positiontab);
                break;

                case P2:
                SDL_BlitSurface(I_P2, NULL, ecran, &positiontab);
                break;

                case BOMB:
                SDL_BlitSurface(I_Bomb, NULL, ecran, &positiontab);
                break;

                case P3:
                SDL_BlitSurface(I_P3, NULL, ecran, &positiontab);
                break;

                case P4:
                SDL_BlitSurface(I_P4, NULL, ecran, &positiontab);
                break;

                case EXPLO:
                SDL_BlitSurface(I_Explo, NULL, ecran, &positiontab);
                break;

                case FUME:
                SDL_BlitSurface(I_Fume, NULL, ecran, &positiontab);
                break;

                case BOX:
                SDL_BlitSurface(I_Box, NULL, ecran, &positiontab);
                break;

                case BONUS:
                SDL_BlitSurface(I_Bonus, NULL, ecran, &positiontab);
                break;

                case P1BOMB:
                SDL_BlitSurface(I_P1Bomb, NULL, ecran, &positiontab);
                break;

                case P2BOMB:
                SDL_BlitSurface(I_P2Bomb, NULL, ecran, &positiontab);
                break;

                case P3BOMB:
                SDL_BlitSurface(I_P3Bomb, NULL, ecran, &positiontab);
                break;

                case P4BOMB:
                SDL_BlitSurface(I_P4Bomb, NULL, ecran, &positiontab);
                break;
            }
            positiontab.x = 34 + positiontab.x; /* Décale la position d'une image (34 pixels) en x */
        }
        positiontab.y = 34 + positiontab.y; /* Décale la position d'une image (34 pixels) en y */
        positiontab.x = 385; /* Réinitialise la position en x */
    }
    SDL_Flip(ecran); /* Actualise l'écran pour afficher toutes les images qui viennent d'être coller */
    return;
}

void affichage_interface(SDL_Surface *ecran, JOUEUR team[5], SDL_Surface *I_interface_bomb, SDL_Surface *I_interface_explo1, SDL_Surface *I_interface_explo2, SDL_Surface *I_interface_explo3, SDL_Surface *I_interface_explo4, SDL_Surface *I_interface_explo5, SDL_Surface *I_interface_explo6, SDL_Surface *I_interface_P1, SDL_Surface *I_interface_P2, SDL_Surface *I_interface_P3, SDL_Surface *I_interface_P4, SDL_Surface *I_interface_dead)
{
    int i, j;

    /* Initialise la position des interfaces de chaque joueur */

    SDL_Rect position_P[5];
    SDL_Rect position_bomb[5];
    SDL_Rect position_explo[5];

    position_P[1].x = 158;
    position_P[2].x = 158;
    position_P[3].x = 1088;
    position_P[4].x = 1088;

    position_P[1].y = 180;
    position_P[2].y = 540;
    position_P[3].y = 180;
    position_P[4].y = 540;

    position_bomb[1].x = 158;
    position_bomb[2].x = 158;
    position_bomb[3].x = 1088;
    position_bomb[4].x = 1088;

    position_bomb[1].y = 218;
    position_bomb[2].y = 578;
    position_bomb[3].y = 218;
    position_bomb[4].y = 578;

    position_explo[1].x = 158;
    position_explo[2].x = 158;
    position_explo[3].x = 1088;
    position_explo[4].x = 1088;

    position_explo[1].y = 234;
    position_explo[2].y = 594;
    position_explo[3].y = 234;
    position_explo[4].y = 594;

    SDL_BlitSurface(I_interface_P1, NULL, ecran, &position_P[1]); /* Affiche l'icône du joueur 1 */
    SDL_BlitSurface(I_interface_P2, NULL, ecran, &position_P[2]); /* Affiche l'icône du joueur 2 */
    SDL_BlitSurface(I_interface_P3, NULL, ecran, &position_P[3]); /* Affiche l'icône du joueur 3 */
    SDL_BlitSurface(I_interface_P4, NULL, ecran, &position_P[4]); /* Affiche l'icône du joueur 4 */

    for(i = 1; i < 5; i++) /* Affiche l'interface de chaque joueur */
    {
        if(team[i].etat == DEAD) /* Affiche une tombe à la place des icônes des joueurs s'ils sont morts */
            SDL_BlitSurface(I_interface_dead, NULL, ecran, &position_P[i]);
        for(j = 0; j < team[i].nb_bombe; j++) /* Affiche le nombre de bombe que le joueur peut poser */
        {
            SDL_BlitSurface(I_interface_bomb, NULL, ecran, &position_bomb[i]); /* Charge l'icône d'une bombe */
            position_bomb[i].x = position_bomb[i].x + 16; /* Décale la position de la prochaine icône de bombe */
        }
        switch(team[i].taille_bombe) /* Affiche la porté des bombes du joueur */
        {
            case 1 :
            SDL_BlitSurface(I_interface_explo1, NULL, ecran, &position_explo[i]); /* Charge l'image correspondant à une porté de 1 */
            break;
            case 2 :
            SDL_BlitSurface(I_interface_explo2, NULL, ecran, &position_explo[i]); /* Charge l'image correspondant à une porté de 2 */
            break;
            case 3 :
            SDL_BlitSurface(I_interface_explo3, NULL, ecran, &position_explo[i]); /* Charge l'image correspondant à une porté de 3 */
            break;
            case 4 :
            SDL_BlitSurface(I_interface_explo4, NULL, ecran, &position_explo[i]); /* Charge l'image correspondant à une porté de 4 */
            break;
            case 5 :
            SDL_BlitSurface(I_interface_explo5, NULL, ecran, &position_explo[i]); /* Charge l'image correspondant à une porté de 5 */
            break;
            case 6 :
            SDL_BlitSurface(I_interface_explo6, NULL, ecran, &position_explo[i]); /* Charge l'image correspondant à une porté de 6 */
            break;
        }
    }

    SDL_Flip(ecran); /* Actualise l'écran pour afficher les images collées précédemment */
}

void affichage_menu(SDL_Surface *ecran, MENU image_menu, SDL_Surface *I_menu_jouer, SDL_Surface *I_menu_credit, SDL_Surface *I_menu_quitter)
{
    /* Initialise la position du menu */
    SDL_Rect position;
    position.x = 0;
    position.y = 0;

    /* Affiche une image différente en fonction de l'endroit du curseur */
    if(image_menu == JOUER) /* Cas où le curseur est sur jouer */
        SDL_BlitSurface(I_menu_jouer, NULL, ecran, &position);
    else if(image_menu == CREDIT) /* Cas où le curseur est sur crédit */
        SDL_BlitSurface(I_menu_credit, NULL, ecran, &position);
    else if(image_menu == QUITTER) /* Cas où le curseur est sur quitter */
        SDL_BlitSurface(I_menu_quitter, NULL, ecran, &position);

    SDL_Flip(ecran); /* Actualise l'écran pour afficher le menu */
}

void credit(SDL_Surface *ecran)
{

    /* Initialise la variable pour la boucle de pause */
    int continuer = 1;

    /* Initialise la surface qui va stocker l'image */
    SDL_Surface *I_credit;

    /* Initialise le variable qui va stocker l'event */
    SDL_Event event;

    /* Initialise la position du crédit */
    SDL_Rect position;
    position.x = 0;
    position.y = 0;

    /* Charge l'image du crédit */
    I_credit = SDL_LoadBMP("credit.bmp");

    /* Colle l'image du crédit sur l'écran */
    SDL_BlitSurface(I_credit, NULL, ecran, &position);

    /* Actualise l'écran pour afficher l'image */
    SDL_Flip(ecran);

    /* Lancement de la boucle de pause */
    while(continuer)
    {
        /* Détection des events */
        SDL_PollEvent(&event);
        switch(event.type) /* Détecte le type de l'event */
        {
        case SDL_KEYDOWN : /* Cas si le joueur a appuyé sur une touche du clavier */
            switch(event.key.keysym.sym)
            {
            case SDLK_SPACE : /* Si le joueur appuie sur espace, il sort de la boucle de pause */
            continuer = 0;
            break;
            }
        }
    }
    menu(ecran); /* Retour au menu */
}

void affichage_victoire(int n_joueur, SDL_Surface *ecran)
{

    /* Initialise la surface qui va stocker l'image */
    SDL_Surface *I_victoire;

    /* Initialise la position de l'écran de victoire */
    SDL_Rect position;
    position.x = 0;
    position.y = 0;

    /* Initialise la variable pour la boucle de pause */
    int continuer = 1;

    /* Initialise le variable qui va stocker l'event */
    SDL_Event event;

    /* Charge l'écran de victoire en fonction du joueur qui a gagné */
    if(n_joueur == 1)
    {
        I_victoire = SDL_LoadBMP("victoire1.bmp");
    }
    if(n_joueur == 2)
    {
        I_victoire = SDL_LoadBMP("victoire2.bmp");
    }
    if(n_joueur == 3)
    {
        I_victoire = SDL_LoadBMP("victoire3.bmp");
    }
    if(n_joueur == 4)
    {
        I_victoire = SDL_LoadBMP("victoire4.bmp");
    }

    /* Colle l'image de l'écran de victoire sur la surface écran */
    SDL_BlitSurface(I_victoire, NULL, ecran, &position);

    /* Actualise l'écran pour afficher l'écran de victoire */
    SDL_Flip(ecran);

    /* Lancement de la fonction de pause */
    while(continuer)
    {
        /* Détection des events */
        SDL_PollEvent(&event);
        switch(event.type) /* Détecte le type de l'event */
        {
        case SDL_KEYDOWN : /* Cas si le joueur a appuyé sur une touche du clavier */
            switch(event.key.keysym.sym)
            {
            case SDLK_SPACE : /* Si le joueur appuie sur espace, il sort de la boucle de pause */
            continuer = 0;
            break;
            }
        }
    }

    menu(ecran); /* Retour au menu */
}
