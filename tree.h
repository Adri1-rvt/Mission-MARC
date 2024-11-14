//
// Created by adrie on 30/10/2024.
//

/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "map.h"
#include "moves.h"

#define NB_possibilities 5
#define NB_choices 3


/**==========PROTOTYPES DES FONCTIONS==========*/
typedef struct s_node
{
    int value;
    int depth;
    t_soil soil_type;
    struct s_node **sons;
    int nbSons; // Taille physique du tableau
} t_node;

t_move* random_possibilities();

t_move* remove_possibility(t_move*, int, int);

t_node *createNode(int, int, t_localisation, t_map);

t_node *create_all_Node(int, int, t_move*, t_localisation, t_map);

int search_min(t_node *);

int path_min(t_node *,int *, int *);


/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#endif


/**
 * Fichier : tree.h (fichier d'en-tête de tree.c)
 * Auteurs : Thomas BOTTALICO, Noe MOOS DEGOUTIN, Adrien RIVET
 * Version : 1.1
 */