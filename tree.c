//
// Created by adrie on 30/10/2024.
//

/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#include "tree.h"


/**==========FONCTIONS DE L'ARBRE==========*/
t_move* random_possibilities() {
    srand(time(NULL));
    t_move* possibilities = (t_move*) malloc(NB_possibilities * sizeof(t_move));   // allouer le tableau de mouvement tiré au hasard
    for(int i = 0; i < NB_possibilities; i++) {
        switch (1 + rand() % 7) {   // prendre le mouvement associé au chiffre tiré et le placer dans le tableau de mouvement
            case 1:
                possibilities[i] = F_10;
                break;
            case 2:
                possibilities[i] = F_20;
                break;
            case 3:
                possibilities[i] = F_30;
                break;
            case 4:
                possibilities[i] = B_10;
                break;
            case 5:
                possibilities[i] = T_LEFT;
                break;
            case 6:
                possibilities[i] = T_RIGHT;
                break;
            case 7:
                possibilities[i] = U_TURN;
                break;
        }
    }
    return possibilities;
}

t_move* remove_possibility(t_move* possibilities, int len, int idx) {
    t_move* new_possibilities = (t_move*) malloc((len-1) * sizeof(t_move));
    int j = 0;
    for (int i = 0; i < len-1; i++){
        if (i == idx) j++;
        new_possibilities[i] = possibilities[j];
        j++;
    }
    return new_possibilities;
}

t_node *createNode(int nb_sons, int depth, t_localisation loc, t_map map) {
    t_node *new_node;                                           //Initialise le nouvel arbre
    new_node = (t_node *) malloc(sizeof(t_node));
    new_node -> value = map.costs[loc.pos.y][loc.pos.x];   // définir le coût de la case
    new_node -> depth = depth;   // définir la profondeur du noeud
    new_node -> soil_type = map.soils[loc.pos.y][loc.pos.x];   // définir le type de sol de la case
    new_node -> nbSons = nb_sons;   // définir son nombre d'enfants
    new_node -> sons = (t_node **) malloc(nb_sons*sizeof(t_node *));
    for (int i = 0; i < nb_sons; i++) new_node->sons[i] = NULL;
    return new_node;
}

t_node *create_all_Node(int nb_possibilities, int depth, t_move* possibilities, t_localisation robot, t_map map) {
    if (depth > NB_choices) return NULL;   // vérifier si la profondeur est supérieur au nombre de choix
    else if (depth == NB_choices || map.costs[robot.pos.y][robot.pos.x] >= 10000) nb_possibilities = 0;   //vérifier si on est à la profondeur la plus basse, donc le dernier choix, ou que la case après le mouvement est une crevasse, le noeud n'aura pas d'enfant
    t_node* node = createNode(nb_possibilities, depth, robot, map);   // initialiser le nouveau noeud
    for (int i = 0; i < nb_possibilities; i++) {
        t_localisation new_loc = robot;
        updateLocalisation(&new_loc, possibilities[i]);   // stocker la nouvelle position du robot selon le mouvement associé dans new_loc
        if (isValidLocalisation(new_loc.pos, map.x_max, map.y_max)) {   // vérifier si la position après le mouvement est valide, on crée les enfants
            t_move* new_possibilities = remove_possibility(possibilities, nb_possibilities, i);   // créer le nouveau tableau de possibilités en retirant la case du noeud qu'on va créer car on l'aura déjà utilisé et on a déjà stocker la position après le mouvement pour connaître le coût
            node -> sons[i] = create_all_Node(nb_possibilities - 1, depth+1, new_possibilities, new_loc, map);   // utiliser la récursivité pour obtenir l'enfant avec les nouveaux paramètres
            free(new_possibilities);   // libèrer la mémoire de new_possibilities
        }
        else node -> sons[i] = NULL;
    }
    return node;
}

int search_min(t_node *node) {
    int min = node -> value;
    if (node -> nbSons!=0) {
        for (int i = 0; i < node -> nbSons; i++) {
            if (node -> sons[i]!=NULL){
                int min_son = search_min(node -> sons[i]);
                if (min_son < min){
                    min = min_son;
                }
            }
        }
    }
    return min;
}

int path_min(t_node *node, int *path, int *path_length) {
    if (node -> nbSons == 0) {   // vérifier que le noeud n'a pas d'enfant
        path[0] = node -> value;   // stocker la valeur du noeud dans path à la position 0
        (*path_length)++;
        return node -> value;
    }
    int min = node -> value;
    for (int i = 0; i < node -> nbSons; i++) {   // parcourir chaque fils
        if (node -> sons[i] != NULL) {   // vérifier le noeud du fils existe
            int temp_length = 0;   // initialiser une variable temporaire de la longueur du chemin du fils
            int *temp_path = (int *) malloc(node -> depth *sizeof(int));   // allouer le tableau dynamique qui stocke temporairement le chemin
            int min_son = path_min(node -> sons[i],temp_path ,&temp_length);   // appeler de manière récursive pour stocker le chemin et la longueur temporaire du fils

            if (min_son < min) {   // vérifier si le minimum du fils est inférieur au minimum actuel
                min = min_son;   // mettre à jour du minimum
                path[0] = node -> value;   // ajouter la valeur du noeud actuel
                for (int j = 0; j < temp_length; j++) path[j+1] = temp_path[j];
                *path_length = temp_length + 1;   // mettre à jour de la longueur totale du chemin
            }
            free(temp_path);   // libérer la mémoire
        }
    }
    return min;
}


/**
 * Fichier : tree.c (fichier gérant les arbres)
 * Auteurs : Thomas BOTTALICO, Noe MOOS DEGOUTIN, Adrien RIVET
 * Version : 1.1
 */