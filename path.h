//
// Created by adrie on 21/11/2024.
//

/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#ifndef UNTITLED1_PATH_H
#define UNTITLED1_PATH_H
#include "node_queue.h"

// Fonction pour récupérer un tableau de nœuds ayant les valeurs minimales
// Paramètre : feuille, pointeur vers un entier
// Retour : pointeur vers une feuille
p_node* tab_of_min(p_node node, int* len);

// Fonction d'appel de la fonction min_leaf_node
// Paramètre : arbre
// Retour : pointeur vers feuille
p_node min_leaf(t_tree t);

// Fonction pour trouver la feuille avec le coût minimum dans un nœud
// Paramètre : pointeur vers feuille
// Retour : pointeur vers feuille
p_node min_leaf_node(p_node node);

//Fonction pour la recherche du meilleur chemin, c'est-à-dire, le cou^t le moins chère
// Paramètre : arbre, pointeur vers entier
// Retour : pointeur vers mouvement
t_move* best_path(t_tree t, int *len);


/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#endif
