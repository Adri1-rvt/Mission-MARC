//
// Created by adrie on 21/11/2024.
//

/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#ifndef UNTITLED1_NODE_QUEUE_H
#define UNTITLED1_NODE_QUEUE_H
#include "tree.h"


/**==========PROTOTYPES DES FONCTIONS==========*/
// structure d'une file sous forme de tableau
typedef struct s_queue_tab
{
    p_node values[MAX];
    int first, last;
} t_queue_tab;

// fonction de création d'une file vide
// paramètre : aucun
// retour : file
t_queue_tab createEmptyQueue();

// fonction d'empilement
// paramètre : pointeur vers une file, cellule
// retour : aucun
void enqueue_node(t_queue_tab *, p_node);

// fonction de dépilement
// paramètre : pointeur vers une file
// retour : cellule
p_node dequeue_node(t_queue_tab *);


/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#endif
