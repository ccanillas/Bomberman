#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"

void pose_bombe(CASES carte[LARGEUR][HAUTEUR], BOMBE all_bombs[], JOUEUR team[], int n_joueur)
{
    if (team[n_joueur].etat == ALIVE && carte[team[n_joueur].position_x][team[n_joueur].position_y] == n_joueur) /*Avant de faire quoi que ce soit on v�rifie si le joueur est vivant*/
    {
        int i;
        clock_t temps = clock();

        for(i = 0; i < TAILLE_TAB_BOMB; ++i) /*Boucle pour trouver la premi�re place libre dans le tableau ou on stocke les bombes*/
        {
            if (all_bombs[i].etat != ALIVE) /*Si la place i est libre dans le tableau, on sort de la boucle*/
                break;
        }
        /*Le i qu'on r�cup�re est donc associer � une place libre*/

        if (team[n_joueur].nb_bombe_actif < team[n_joueur].nb_bombe) /*On v�rifie que le joueur peut poser une bombe*/
        {
            carte[team[n_joueur].position_x][team[n_joueur].position_y] = n_joueur + 10; /*On actualise la carte en pla�ant un "joueur plus bombe"*/

            /*Initialisation de la bombe pos�e*/
            all_bombs[i].etat = ALIVE; /*Si elle est active*/
            all_bombs[i].owner = n_joueur; /*Son possesseur*/
            /*Ses coordon�es :*/
            all_bombs[i].position_x = team[n_joueur].position_x;
            all_bombs[i].position_y = team[n_joueur].position_y;
            all_bombs[i].tspawn = temps/CLOCKS_PER_SEC; /*Le moment ou elle � �t� pos�e*/

            team[n_joueur].nb_bombe_actif ++; /*On actualise le nombre de bombe que le joueur � pos�*/

        }
    }

}

void pose_explo(EXPLOSION all_explo[], int x, int y)
{
    int i;

    for(i = 0; i < TAILLE_TAB_EXPLO; ++i) /*Boucle pour trouver la premi�re place libre dans le tableau ou on stocke les explosions*/
    {
        if (all_explo[i].etat != ALIVE) /*Si la place i est libre dans le tableau, on sort de la boucle*/
            break;
    }
    /*Le i qu'on r�cup�re est donc associer � une place libre*/

        /*Initialisation de l'explosion pos�e*/
        all_explo[i].etat = ALIVE; /*Si elle est active*/
        /*Ses coordon�es :*/
        all_explo[i].position_x = x;
        all_explo[i].position_y = y;
        all_explo[i].tspawn = clock()/CLOCKS_PER_SEC; /*Le moment ou elle � �t� pos�e*/

}

void explose_bombe(CASES carte[LARGEUR][HAUTEUR], BOMBE all_bombs[], int n_bombe, JOUEUR team[], EXPLOSION all_explo[])
{
    DIRECTION d;
    int p, x = all_bombs[n_bombe].position_x, y = all_bombs[n_bombe].position_y, stop, i, x1,y1;

    team[all_bombs[n_bombe].owner].nb_bombe_actif--; /*On actualise le nombre de bombe que le joueur � pos�*/

    /*Reinitialition de l'emplacement dans le tableau de bombe*/
    all_bombs[n_bombe].etat = DEAD;
    all_bombs[n_bombe].tspawn = -1;


    if(carte[x][y] >= 11 && carte[x][y] <= 14)
        team[carte[x][y]-10].etat = DEAD; /*Si il y a un joueur sur la bombe on le fait mourrir*/
    carte[x][y] = EXPLO;  /*On actualise la carte en pla�ant une explosion*/
    pose_explo(all_explo, x, y); /*On appelle la fonction pour stocker l'explosion pos�e*/

    for (d = DOWN; d <= RIGHT; ++d) /*Boucle qui parcoure les 4 dirrections*/
    {
        stop = 0; /*Remise � 0 de la valeur de la variable qui arr�te la deuxieme boucle*/
        for(p = 1; (p <= team[all_bombs[n_bombe].owner].taille_bombe) && (stop != 1); ++p) /*Boucle qui fait avancer l'explosion*/
        {
            /*Recup�ration de la position de la bombe*/
            x1 = x;
            y1 = y;

            switch (d) /*Modification des coordon�s de l'explosion � placer en fonction de la dirrection*/
            {
                case DOWN: /*Si c'est vers le bas*/
                    y1 += p; /*On augmente sur y*/
                    break;

                case UP: /*Si c'est vers le haut*/
                    y1 -= p; /*On diminue sur y*/
                    break;

                case LEFT: /*Si c'est vers la droite*/
                    x1 -= p;  /*On diminue sur x*/
                    break;

                case RIGHT: /*Si c'est vers la gauche*/
                    x1 += p;  /*On augmente sur x*/
                    break;
            }

            switch (carte[x1][y1]) /*Action � faire selon le block � exploser*/
            {
                case GROUND: /*Si c'est du sol, on place juste une explosion*/
                    carte[x1][y1] = EXPLO;
                    pose_explo(all_explo, x1, y1);
                    break;

                case P1:
                case P2: /*Si c'est un joueur*/
                case P3:
                case P4:
                    team[carte[x1][y1]].etat = DEAD; /*On le tue*/
                    carte[x1][y1] = EXPLO; /*Et on place une explosion*/
                    pose_explo(all_explo, x1, y1);
                    break;

                case BOMB: /*Si c'est une bombe*/
                    for(i = 0; i < TAILLE_TAB_BOMB; ++i) /*On parcoure le tableau de bombe*/
                    {
                        if ((x1 == all_bombs[i].position_x) && (y1 == all_bombs[i].position_y)) /*On r�cup�re ses coordon�es*/
                        {
                            explose_bombe(carte, all_bombs, i,team, all_explo); /*On la fait exploser*/
                        }
                    }
                    stop = 1; /*On arr�te la propagation de l'explosion*/
                break;

                case EXPLO: /*Si c'est une explosion*/
                case FUME: /*Ou de la fum�e*/
                    for(i = 0; i < TAILLE_TAB_EXPLO; ++i) /*On parcoure le tableau d'explosion*/
                    {
                        if ((x1 == all_explo[i].position_x) && (y1 == all_explo[i].position_y)) /*On r�cup�re ses coordon�es*/
                        {
                            all_explo[i].tspawn = clock() / CLOCKS_PER_SEC; /*On reinitialise son timer*/
                        }
                    }
                    break;

                case BOX: /*Si c'est une caisse*/
                    carte[x1][y1] = FUME; /*On pose une fum�e*/
                    pose_explo(all_explo, x1, y1); /*Et on la rentre dans le tableau d'explosion*/
                    stop = 1; /*On arr�te la propagation*/
                    break;

                case BONUS: /*Si c'est un bonus*/
                    carte[x1][y1] = FUME; /*On replace une fum�e (sorte de reinitialisation)*/
                    pose_explo(all_explo, x1, y1); /*Et on la rentre dans le tableau d'explosion*/
                    break;

                case WALL:
                    stop = 1; /*On arr�te la propagation*/
                    break;

                case P1BOMB:
                case P2BOMB: /*Si c'est un "joueur plus bombe"*/
                case P3BOMB:
                case P4BOMB:
                    team[carte[x1][y1]-10].etat = DEAD; /*On tue le joueur*/
                    for(i = 0; i < TAILLE_TAB_BOMB; ++i) /*On fait exploser la bombe*/
                    {
                        if ((x1 == all_bombs[i].position_x) && (y1 == all_bombs[i].position_y))
                        {
                            explose_bombe(carte, all_bombs, i,team, all_explo);
                        }
                    }
                    stop = 1; /*On arr�te la propagation*/
                    break;
            }
        }
    }
}

void remove_explo(CASES carte[LARGEUR][HAUTEUR], EXPLOSION all_explo[], int n_explo)
{
    /*R�cup�ration des coordonn�es*/
    int x = all_explo[n_explo].position_x, y = all_explo[n_explo].position_y;

    /*Reinitialition de l'emplacement dans le tableau d'explosion*/
    all_explo[n_explo].etat = DEAD;
    all_explo[n_explo].tspawn = -1;

    switch (carte[x][y]) /*Action � faire selon le block � enlever*/
    {
        case EXPLO:
            carte[x][y] = GROUND; /*Pour une explosion, on replace juste du sol*/
            break;
        case FUME:
            spawn_bonus(carte, x, y); /*Pour une fum�e on fait ou pas apparaitre un bonus*/
            break;
    }


}

void time_checker (CASES carte[LARGEUR][HAUTEUR], BOMBE all_bombs[], EXPLOSION all_explo[], JOUEUR team[])
{
    int i;
    float temps = clock() / CLOCKS_PER_SEC; /*On r�cup�re le temps a cet instant*/

    for(i = 0; i < TAILLE_TAB_EXPLO; ++i) /*On parcour le tableau d'explosion*/
    {
        if (i < TAILLE_TAB_BOMB) /*Si i < 40, on parcour le tableau de bombe*/
        {
            if ((all_bombs[i].tspawn != -1) && ((temps - all_bombs[i].tspawn) >= T_BOMBE)) /*Si la bombe � �t� pos�e il y a suffisament longtemps*/
            {
                explose_bombe(carte, all_bombs, i, team, all_explo); /*On la fait exploser*/
            }
        }
        if ((all_explo[i].etat == ALIVE) && (temps - all_explo[i].tspawn) >= T_EXPLO) /*Si l'explosion � �t� pos�e il y a suffisament longtemps*/
            {
                remove_explo(carte, all_explo, i); /*On l'enl�ve*/
            }
    }
}
