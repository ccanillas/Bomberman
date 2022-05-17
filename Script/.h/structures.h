/* Fichier structures.h

Usage : comporte toute les structures du jeu

Projet Bomberman 1A

*/

#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED                                           /* Déclaration des grandes constantes */

    #define T_BOMBE               2                                     /* Compte à rebours des bombes : 2 secondes */
    #define T_EXPLO             0.8                                     /* Durée d'une explosion : 0.8 secondes */
    #define T_DEPLACEMENT      0.15                                     /* Temps entre chaque déplacement */
    #define HAUTEUR              13                                     /* Hauteur de la map : 15 cases */
    #define LARGEUR              15                                     /* Largeur de la map : 13 cases */
    #define INIT_NB_BOMBE         1                                     /* Nombre de bombes posable intial : 1 */
    #define INIT_TAILLE_BOMBE     1                                     /* Taille de bombe initiale : 1 case */
    #define TAILLE_EXPLO_MAX      6                                     /* Taille maximale des explosions : 10 cases */
    #define NB_BOMBES_MAX         6                                     /* Nombre de bombes posable par joueur au maximum */
    #define NB_JOUEURS            4                                     /* On définit ici le nombre de joueurs (wouah merci captain obvious !) */
    #define TAILLE_TAB_BOMB      24                                     /* Taille du tableau des bombes */
    #define TAILLE_TAB_EXPLO    144                                     /* Taille du tableau des explosions */



typedef enum {DEAD,ALIVE} ETAT;
typedef enum {DOWN,UP,LEFT,RIGHT} DIRECTION;
typedef enum {GROUND,P1,P2,P3,P4,BOMB,EXPLO,FUME,BOX,BONUS,WALL,P1BOMB,P2BOMB,P3BOMB,P4BOMB} CASES;
typedef enum {JOUER, CREDIT, QUITTER} MENU;

typedef struct                                              /* Structure d'un joueur : */
{
ETAT etat;                                                  /* Est-il en vie ? */
int position_x;                                             /* Où est-il ? */
int position_y;
int nb_bombe;                                               /* Combien de bombes peut-il poser ? */
int taille_bombe;                                           /* Quelle sera la taille des explosions de ses bombes ? */
int nb_bombe_actif;                                         /* Combien de bombe a-t-il posé qui n'ont pas encore explosé ? */
float last_input ;                                          /* Quand a-t-il bougé pour la dernière fois ? (limitation de la vitesse de déplacement) */
} JOUEUR;

typedef struct                                              /* Structure d'une bombe */
{
ETAT etat;                                                  /* Est-elle active ? (si non, on appelle l'explosion) */
int owner;                                                  /* A qui appartient cette bombe ? */
float tspawn;                                               /* Quand a-t-elle été posée ? */
int position_x;                                             /* Sa position */
int position_y;
} BOMBE;

typedef struct                                              /* Structure d'une explosion */
{
    ETAT etat;                                              /* Est-elle active ? */
    int position_x;                                         /* Sa position */
    int position_y;
    float tspawn;                                           /* Moment d'apparition */
} EXPLOSION;

#endif // STRUCTURES_H_INCLUDED
