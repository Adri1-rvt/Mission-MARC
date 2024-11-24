//
// Created by adrie on 21/11/2024.
//

/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#include "path.h"


/**==========FONCTIONS==========*/
p_node* tab_of_min(p_node node, int* len){
    int min_val = search_min_node(node);   // Trouver la valeur minimale dans l'arbre à partir du nœud donné
    p_node* min_leaf = (p_node*) malloc(MAX * sizeof(p_node));   // Allouer de la mémoire pour stocker les feuilles ayant la valeur minimale

    // Créer et initialiser une file vide
    t_queue_tab q;
    p_node cur;
    q = createEmptyQueue();
    enqueue_node(&q, node);   // Enfiler le nœud de départ dans la file

    // Parcourir la file
    while (q.first != q.last){
        cur = dequeue_node(&q);   // Défiler un nœud de la file
        if(cur -> value == min_val){   // Vérifier si la valeur du nœud courant est la valeur minimale cherchée
            int depth_of_min = cur -> depth;   // Obtenir la profondeur de la feuille minimale actuelle
            while (cur -> depth == depth_of_min && q.first != q.last){   // Parcourir les nœuds à la même profondeur// Parcourir les nœuds à la même profondeur
                if(cur -> value == min_val){   // Si la valeur du nœud courant est encore la valeur minimale
                    min_leaf[*len] = cur;   // Ajouter ce nœud dans le tableau des feuilles minimales
                    //printf("cur = %d, minleaf[] = %d, len = %d\n", cur->value, min_leaf[*len]->value, *len);
                    (*len)++;   // Augmenter le compteur de longueur
                }
                cur = dequeue_node(&q);   // Défiler le prochain nœud
            }
            return min_leaf;   // Retourner le tableau des feuilles minimales
        }
        else if (cur -> nbSons != 0){   // Si le nœud courant a des fils (des enfants)
            for (int i = 0; i < cur -> nbSons; i++) {   // Parcourir tous les fils du nœud courant
                if (cur -> sons[i] != NULL) enqueue_node(&q,cur -> sons[i]);   // Enfiler chaque fils non nul dans la file
            }
        }
    }
    return NULL;   // Si aucune feuille minimale n'est trouvée, retourner NULL
}

p_node min_leaf(t_tree t) {
    return min_leaf_node(t.root);   // appeler la fonction min_leaf_node
}

p_node min_leaf_node(p_node node){
    int len = 0, cost = 0, cheaper = 10000, idx;   // déclarer des variables pour la longueur, le coût, le coût minimum et l'index de la feuille la moins chère
    p_node* tab_min = tab_of_min(node, &len);   // récupérer un tableau de feuilles avec le coût minimum à partir d'un nœud

    // parcourir toutes les feuilles dans le tableau tab_min
    for (int i = 0; i < len; i++){
        p_node cur = tab_min[i];   // récupérer la feuille courante
        // calculer le coût total de la feuille en remontant vers la racine
        while (cur != NULL) {
            cost += cur -> value;
            cur = cur -> parent;
        }
        // Trouver la feuille avec le coût minimum
        if (cost < cheaper){
            cheaper = cost;
            idx = i;
        }
        cost = 0;   // réinitialiser le coût pour la prochaine itération
    }
    return tab_min[idx];   // retourner la feuille avec le coût minimum
}

t_move* best_path(t_tree t, int *len){
    p_node leaf = min_leaf(t);   // trouver la feuille avec la valeur minimale dans l'arbre
    int depth = leaf -> depth;   // récupérer la profondeur de cette feuille
    *len = depth - 1;   // mettre à jour la longueur du chemin
    t_move* path = (t_move*) malloc((depth) * sizeof(t_move));   // allouer de la mémoire pour stocker le chemin

    // remplir le chemin en remontant de la feuille vers la racine
    for (int i = depth - 1; i >= 0; i--){
        path[i] = leaf -> mouvement;   // copier le mouvement de la feuille dans le chemin
        leaf = leaf -> parent;   // remonter au noeud parent
    }
    return path;   // retourner le chemin
}


/**
 * Fichier : path.c (fichier gérant les chemins)
 * Auteurs : Thomas BOTTALICO, Noe MOOS DEGOUTIN, Adrien RIVET
 * Version : 1.1
 */
