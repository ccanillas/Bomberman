#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "Bombe.h"
#include "deplacement.h"
#include "initialisation.h"
#include <SDL.h>
#include "victoire.h"

void jeu(SDL_Surface *ecran)
{
    /* Initialisation de la variable de boucle de jeu */
    int continuer = 1;

    /* Initialisation de la variable de victoire */
    int a_gagne = 0;

    SDL_Event event; /* initialisation de l'event*/

    CASES carte[LARGEUR][HAUTEUR]; /* initialisation de la carte*/
    JOUEUR team[NB_JOUEURS+1]; /* Initialisation du tableau des joueurs */
    BOMBE all_bombs[TAILLE_TAB_BOMB]; /* Initalisation du tableau des bombes */
    EXPLOSION all_explo[TAILLE_TAB_EXPLO]; /* Initalisation du tableau des bombes */

    /* Initialise la position du fond */
    SDL_Rect position;
    position.x = 0;
    position.y = 0;

    /* Création de toutes les surfaces qui vont stocker les images du jeu pour qu'elles soient chargées
    avant le lancement de la boucle de jeu et ainsi éviter de les recharger à chaque fois et diminuer la
    consomation en ressources */
    SDL_Surface *I_Ground, *I_P1, *I_P2, *I_P3, *I_P4, *I_Bomb, *I_Explo, *I_Fume, *I_Box, *I_Bonus, *I_Wall, *I_Fond, *I_interface_bomb, *I_interface_explo1, *I_interface_explo2, *I_interface_explo3, *I_interface_explo4, *I_interface_explo5, *I_interface_explo6, *I_interface_P1, *I_interface_P2, *I_interface_P3, *I_interface_P4, *I_interface_dead, *I_P1Bomb, *I_P2Bomb, *I_P3Bomb, *I_P4Bomb;

    /* Chargement de toutes les images qui vont être utilisées dans la boucle de jeu */
    I_Ground = SDL_LoadBMP("ground.bmp");
    I_P1 = SDL_LoadBMP("p1.bmp");
    I_P2 = SDL_LoadBMP("p2.bmp");
    I_P3 = SDL_LoadBMP("P3.bmp");
    I_P4 = SDL_LoadBMP("P4.bmp");
    I_Bomb = SDL_LoadBMP("bomb.bmp");
    I_Explo = SDL_LoadBMP("explo.bmp");
    I_Fume = SDL_LoadBMP("fume.bmp");
    I_Box = SDL_LoadBMP("box.bmp");
    I_Bonus = SDL_LoadBMP("bonus.bmp");
    I_Wall = SDL_LoadBMP("wall.bmp");
    I_Fond = SDL_LoadBMP("fond.bmp");
    I_P1Bomb = SDL_LoadBMP("p1bomb.bmp");
    I_P2Bomb = SDL_LoadBMP("p2bomb.bmp");
    I_P3Bomb = SDL_LoadBMP("p3bomb.bmp");
    I_P4Bomb = SDL_LoadBMP("p4bomb.bmp");
    I_interface_bomb = SDL_LoadBMP("interface_bomb.bmp");
    I_interface_explo1 = SDL_LoadBMP("interface_explo1.bmp");
    I_interface_explo2 = SDL_LoadBMP("interface_explo2.bmp");
    I_interface_explo3 = SDL_LoadBMP("interface_explo3.bmp");
    I_interface_explo4 = SDL_LoadBMP("interface_explo4.bmp");
    I_interface_explo5 = SDL_LoadBMP("interface_explo5.bmp");
    I_interface_explo6 = SDL_LoadBMP("interface_explo6.bmp");
    I_interface_P1 = SDL_LoadBMP("p1.bmp");
    I_interface_P2 = SDL_LoadBMP("p2.bmp");
    I_interface_P3 = SDL_LoadBMP("p3.bmp");
    I_interface_P4 = SDL_LoadBMP("p4.bmp");
    I_interface_dead = SDL_LoadBMP("interface_dead.bmp");



    initialisation_map(carte);

    initialisation_joueur(team, carte);

    initialisation_bombes_explosions(all_bombs, all_explo);

    /* Colle le fond du jeu sur l'écran */
    SDL_BlitSurface(I_Fond, NULL, ecran, &position);

    affichage_jeu(carte, ecran, I_Ground, I_P1, I_P2, I_P3, I_P4, I_Bomb, I_Explo, I_Fume, I_Box, I_Bonus, I_Wall, I_P1Bomb, I_P2Bomb, I_P3Bomb, I_P4Bomb);

    affichage_interface(ecran, team, I_interface_bomb, I_interface_explo1, I_interface_explo2, I_interface_explo3, I_interface_explo4, I_interface_explo5, I_interface_explo6, I_interface_P1, I_interface_P2, I_interface_P3, I_interface_P4, I_interface_dead);


    /* Lancement de la boucle de jeu */
    while(continuer)
    {
        /* Detecte si un joueur a gagné */
        a_gagne = victoire(team);

        if(a_gagne != 0) /* Si un joueur a gagné on sort de la boucle sinon on continue */
            continuer = 0;

        /* Affichage de la carte */
        affichage_jeu(carte, ecran, I_Ground, I_P1, I_P2, I_P3, I_P4, I_Bomb, I_Explo, I_Fume, I_Box, I_Bonus, I_Wall, I_P1Bomb, I_P2Bomb, I_P3Bomb, I_P4Bomb);

        /* Affichage de l'interface */
        affichage_interface(ecran, team, I_interface_bomb, I_interface_explo1, I_interface_explo2, I_interface_explo3, I_interface_explo4, I_interface_explo5, I_interface_explo6, I_interface_P1, I_interface_P2, I_interface_P3, I_interface_P4, I_interface_dead);

        /* Fait exploser les bombes et enlève les explosions */
        time_checker(carte, all_bombs, all_explo, team);

        /* Détéction des events */
        SDL_PollEvent(&event);
        switch(event.type) /* Détéction du type d'event */
        {
        case SDL_KEYDOWN : /* Cas si le joueur a appuyé sur une touche */
            switch(event.key.keysym.sym)
            {
            case SDLK_w: /* Touche du joueur 1 pour aller vers le haut */
                deplacement_up(carte, team, P1);
                break;
            case SDLK_s : /* Touche du joueur 1 pour aller vers le bas */
                deplacement_down(carte, team, P1);
                break;
            case SDLK_a : /* Touche du joueur 1 pour aller vers la gauche */
                deplacement_left(carte, team, P1);
                break;
            case SDLK_d : /* Touche du joueur 1 pour aller vers la droite */
                deplacement_right(carte, team, P1);
                break;
            case SDLK_UP: /* Touche du joueur 4 pour aller vers le haut */
                deplacement_up(carte, team, P4);
                break;
            case SDLK_DOWN : /* Touche du joueur 4 pour aller vers le bas */
                deplacement_down(carte, team, P4);
                break;
            case SDLK_LEFT : /* Touche du joueur 4 pour aller vers la gauche */
                deplacement_left(carte, team, P4);
                break;
            case SDLK_RIGHT : /* Touche du joueur 4 pour aller vers la droite */
                deplacement_right(carte, team, P4);
                break;
            case SDLK_o : /* Touche du joueur 3 pour aller vers le haut */
                deplacement_up(carte, team, P3);
                break;
            case SDLK_l : /* Touche du joueur 3 pour aller vers le bas */
                deplacement_down(carte, team, P3);
                break;
            case SDLK_k : /* Touche du joueur 3 pour aller vers la gauche */
                deplacement_left(carte, team, P3);
                break;
            case SDLK_SEMICOLON : /* Touche du joueur 3 pour aller vers la droite */
                deplacement_right(carte, team, P3);
                break;
            case SDLK_p : /* Touche du joueur 3 pour poser une bombe */
                pose_bombe(carte, all_bombs, team, P3);
                break;
            case SDLK_t : /* Touche du joueur 2 pour aller vers le haut */
                deplacement_up(carte, team, P2);
                break;
            case SDLK_g : /* Touche du joueur 2 pour aller vers le bas */
                deplacement_down(carte, team, P2);
                break;
            case SDLK_f : /* Touche du joueur 2 pour aller vers la gauche */
                deplacement_left(carte, team, P2);
                break;
            case SDLK_h : /* Touche du joueur 2 pour aller vers la droite */
                deplacement_right(carte, team, P2);
                break;
            case SDLK_y : /* Touche du joueur 2 pour poser une bombe */
                pose_bombe(carte, all_bombs, team, P4);
                break;
            case SDLK_e : /* Touche du joueur 1 pour poser une bombe */
                pose_bombe(carte, all_bombs, team, P1);
                break;
            case SDLK_RCTRL : /* Touche du joueur 4 pour poser une bombe */
                pose_bombe(carte, all_bombs, team, P2);
                break;
            }
        }
    }

    /* Affiche l'écran de victoire */
    affichage_victoire(a_gagne, ecran);
}


void menu(SDL_Surface *ecran)
{
    /* Initialise la variable pour la boucle du menu */
    int continuer = 1;

    /* Initialise l'event */
    SDL_Event event;

    /* Création des trois surfaces qui vont stocker les images du menu pour qu'elles soient chargées
    avant le lancement de la boucle du menu */
    SDL_Surface *I_menu_jouer, *I_menu_credit, *I_menu_quitter;

    /* Chargement des trois images du menu */
    I_menu_jouer = SDL_LoadBMP("menu_jouer.bmp");
    I_menu_credit = SDL_LoadBMP("menu_credit.bmp");
    I_menu_quitter = SDL_LoadBMP("menu_quitter.bmp");

    MENU image = JOUER; /* Variable qui définit quel menu doit être afficher */

    int temps = 0; /* Initialisation de la clock qui permet de fluidifier la séléction du menu */

    /* Lancement de la boucle du menu */
    while(continuer)
    {

        affichage_menu(ecran, image, I_menu_jouer, I_menu_credit, I_menu_quitter);

        /* Détéction des events */
        SDL_PollEvent(&event);
        switch(event.type) /* Détéction du type d'event */
        {
        case SDL_KEYDOWN : /* Cas si le joueur a appuyé sur une touche */
            switch(event.key.keysym.sym)
            {
            case SDLK_LEFT :
            /* Si le joueur a appuyé sur la touche gauche décale le curseur vers la gauche */
                if(((clock() - temps)/CLOCKS_PER_SEC) > 0.01) /* Si le temps entre deux inputs est inférieur à 0.01 alors il ne se passe rien */
                {
                    if(image == 0) /* Dans le cas ou le curseur est sur le premier choix on décale le curseur sur le troisième */
                        image = 2;
                    else /* Sinon on décale vers la gauche d'un choix */
                        image = (image - 1) % 3;
                    temps = clock(); /* Actualise le temps du dernier input */
                }
                break;

            case SDLK_RIGHT : /* Si le joueur a appuyé sur la touche droite décale le curseur vers la droite */
                if(((clock() - temps)/CLOCKS_PER_SEC) > 0.01)
                {
                    image = (image + 1) % 3;
                    temps = clock();
                }
                break;

            case SDLK_SPACE : /* Si le joueur appuie sur la touche espace alors la boucle menu s'arrête et retourne la valeur du choix séléctionné */
                continuer = 0;
                break;
            }
        }
    }

    if(image == JOUER) /* Si le curseur était sur jouer alors lance la fonction jeu */
        jeu(ecran);
    else if(image == CREDIT)
        credit(ecran); /* Si le curseur était sur crédit alors lance la fonction crédit */
    return; /* Si le curseur etait sur quitter quitte la fonction menu qui retourn au main et termine le programme */
}
