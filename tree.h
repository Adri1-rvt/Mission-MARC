//
// Created by adrie on 22/10/2024.
//

/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "map.h"
#include "moves.h"

#define NB_possibilities 9
#define NB_choices 5
#define MAX 18730


/**==========PROTOTYPES DES FONCTIONS==========*/
// Structure des feuilles
typedef struct s_node
{
    int value;
    int depth;
    t_move mouvement;
    t_soil soil_type;
    struct s_node *parent;
    struct s_node **sons;
    int nbSons;
} t_node;

// Structure des pointeurs sur une feuille
typedef struct s_node t_node, *p_node;

// Structure des arbres
typedef struct s_tree
{
    p_node root;
} t_tree;


// Fonction pour supprimer un mouvement d'une liste de mouvements
// Paramètre : entiers, pointeur sur mouvement
// Retour : pointeur sur mouvement
t_move* remove_move(t_move*, int, int);

// Fonction pour créer un nouveau nœud
// Paramètre : entiers, mouvements, localisation, map, pointeur sur feuille
// Retour : pounteur sur feuille
p_node createNode(int nb_sons, int depth, t_move mouvement, t_localisation loc, t_map map, p_node node);

// Fonction pour créer tous les nœuds de l'arbre des mouvements possibles
// Paramètre : entiers, mouvement, pointeur sur mouvement, lovalisation, map, pointeur sur feuille
// Retour : pointeur sur feuille
p_node create_all_Node(int nb_poss, int depth, t_move mouvement, t_move* possibilities, t_localisation robot, t_map map, p_node parent_node);

// Fonction pour créer un arbre des mouvements possibles
// Paramètre : entiers, mouvement, pointeur sur mouvement, localisation, map
// Retour : arbre
t_tree create_tree(int nb_poss, int depth, t_move mouvement, t_move* possibilities, t_localisation robot, t_map map);

// Fonction d'appel de search_min_node
// Paramètre : arbre
// Retour : entier
int search_min(t_tree);

//Fonction pour chercher une feuille de valeur minimum
// Paramètre : pointeurr sur feuille
// Retour : entier
int search_min_node(p_node node);

//Fonction pour chercher le nombre de valeur minimum
// Paramètre : pointeur sur feuille, entier
// Retour : entier
int nb_min(t_node *node, int min);


/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#endif


/**
 * Fichier : tree.h (fichier d'en-tête de tree.c)
 * Auteurs : Thomas BOTTALICO, Noe MOOS DEGOUTIN, Adrien RIVET
 * Version : 1.1
 */
