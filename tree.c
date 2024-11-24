//
// Created by adrie on 22/10/2024.
//

/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#include "tree.h"


/**==========FONCTIONS DE L'ARBRE==========*/
t_move* remove_move(t_move* moves, int len, int idx){
    t_move* new_moves = (t_move*) malloc((len-1)*sizeof(t_move));   // Allouer de la mémoire pour une nouvelle liste de mouvements
    int j = 0;   // Initialiser un index pour la liste originale
    for (int i = 0; i < len-1; i++){    // Parcourir tous les mouvements dans la liste originale sauf le dernier
        if (i == idx) j++;   // Si l'index courant correspond à l'index à supprimer, décaler l'index de la liste originale
        new_moves[i] = moves[j];   // Copier le mouvement de la liste originale vers la nouvelle liste
        j++;   // Incrementer l'index de la liste originale
    }
    return new_moves;   // Retourner la nouvelle liste de mouvements
}

p_node createNode(int nb_sons, int depth, t_move mouvement, t_localisation loc, t_map map, p_node node){
    p_node new_node;   // Déclaration d'un pointeur pour le nouveau nœud
    new_node = (t_node *)malloc(sizeof(t_node));   // Allouer de la mémoire pour la structure du nœud
    new_node -> value = map.costs[loc.pos.y][loc.pos.x];   // Initialiser la valeur du nouveau nœud avec le coût de la position dans la carte
    new_node -> depth = depth;   // Initialiser la profondeur du nouveau nœud
    new_node -> mouvement = mouvement;   // Initialiser le mouvement associé au nouveau nœud
    new_node -> parent = node;   // Initialiser le parent du nouveau nœud
    new_node -> soil_type = map.soils[loc.pos.y][loc.pos.x];   // Initialiser le type de sol du nouveau nœud à partir de la carte
    new_node -> nbSons = nb_sons;   // Initialiser le nombre de fils (enfants) du nouveau nœud
    new_node -> sons = (t_node **)malloc(nb_sons*sizeof(t_node *));   // Allouer de la mémoire pour les fils du nœud
    for (int i = 0; i < nb_sons; i++) new_node -> sons[i] = NULL;   // Initialiser tous les fils à NULL
    return new_node;   // Retourner le nouveau nœud créé
}

p_node create_all_Node(int nb_poss, int depth, t_move mouvement, t_move* possibilities, t_localisation robot, t_map map, p_node parent_node){   //La fonction ne prends pas en compte si on avance de plus de 10 mètres ou si on a déjà marché sur une crevasse
    if (depth > NB_choices) return NULL;   // Si la profondeur dépasse le nombre de choix, retourner NULL                                                                               //Si la profondeur est supérieur au nombre de choix, on retourne NULL
    else if (depth == NB_choices || map.costs[robot.pos.y][robot.pos.x] >= 10000) nb_poss = 0;   // Si on est à la profondeur la plus bas, donc le dernier choix, ou que la case après le mouvement est une crevasse, le noeud n'aura pas d'enfant
    p_node node = createNode(nb_poss, depth, mouvement, robot, map, parent_node);   // Initialiser le nouveau noeud
    for (int i = 0; i < nb_poss; i++) {   // Parcourir toutes les possibilités de mouvements
        t_localisation new_loc = robot;   // Stocker la nouvelle position du robot selon le mouvement associé dans `new_loc`
        updateLocalisation(&new_loc, possibilities[i]);

        if (isValidLocalisation(new_loc.pos, map.x_max, map.y_max)) {   // Si la position après le mouvement est valide, créer les enfants
            t_move* new_possibilities = remove_move(possibilities, nb_poss, i);   // Créer le nouveau tableau de possibilités en retirant le mouvement courant
            node -> sons[i] = create_all_Node(nb_poss - 1, depth+1, possibilities[i], new_possibilities, new_loc, map, node);   // Utiliser la récursivité pour créer les nœuds enfants avec les nouveaux paramètres
            free(new_possibilities);   // Libérer la mémoire allouée pour `new_possibilities`
        }
        else node -> sons[i] = NULL;   // Si la position après le mouvement n'est pas valide, ne pas créer d'enfant pour le nœud courant
    }
    return node;   // Retourner le nœud courant avec ses enfants créés
}

t_tree create_tree(int nb_poss, int depth, t_move mouvement, t_move* possibilities, t_localisation robot, t_map map){
    t_tree t;   // Déclarer une variable d'arbre
    t.root = create_all_Node(nb_poss, depth, mouvement, possibilities, robot, map, NULL);   // Initialiser la racine de l'arbre en créant tous les nœuds
    return t;   // Retourner l'arbre créé
}

int search_min(t_tree t){
    return search_min_node(t.root);   // Appeler la fonction search_mîn
}

int search_min_node(p_node node){
    int min = node -> value;   // Initialiser la valeur minimale avec celle du nœud actuel
    if (node -> nbSons != 0){   // Si le nœud a des fils (enfants)
        for (int i = 0; i < node -> nbSons; i++) {   // Parcourir tous les fils du nœud
            if (node -> sons[i] != NULL){   // Si le fils n'est pas nul
                int min_son = search_min_node(node -> sons[i]);   // Rechercher la valeur minimale récursivement dans le fils
                if (min_son < min) min = min_son;   // Mettre à jour la valeur minimale si celle du fils est inférieure
            }
        }
    }
    return min;   // Retourner la valeur minimale trouvée
}

int nb_min(p_node node, int min){
    int nb = 0;   // Initialiser le compteur de nœuds à 0
    if (node -> nbSons != 0){   // Parcourir tous les fils du nœud
        for (int i = 0; i < node -> nbSons; i++) if (node -> sons[i] != NULL) nb += nb_min(node -> sons[i], min);   // Si le fils n'est pas nul, ajouter le résultat de l'appel récursif au compteur
    }
    if (node -> value == min) nb += 1;   // Si la valeur du nœud est égale à `min`, incrémenter le compteur
    return nb;   // Retourner le nombre de nœuds ayant la valeur `min`
}


/**
 * Fichier : tree.c (fichier gérant les arbres)
 * Auteurs : Thomas BOTTALICO, Noe MOOS DEGOUTIN, Adrien RIVET
 * Version : 1.1
 */
