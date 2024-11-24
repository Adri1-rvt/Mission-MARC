//
// Created by adrie on 21/11/2024.
//

/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#include "node_queue.h"


/**==========FONCTIONS==========*/
t_queue_tab createEmptyQueue()
{
    t_queue_tab q;   // créer une file q de type t_queue
    q.first = q.last = 0;   // initialiser first et last à 0
    return q;   // retourner la file
}

void enqueue_node(t_queue_tab *pq, p_node val)
{
    int pos = pq -> last % MAX;   // récupérer la position de la dernière case vide de notre file
    pq -> values[pos] = val;   // insérer la valeur en fin de file
    pq -> last = pq -> last + 1;   // mettre à jour la position du dernier élément dans la file
}

p_node dequeue_node(t_queue_tab *pq)
{
    p_node res;
    int pos = pq -> first % MAX;   // récupérer la position de la première case vide de notre file
    res = pq -> values[pos];   // récuperer la valeur du premier élément de la file
    pq -> first = pq -> first + 1;   // mettre à jour la position du premier élément dans la file
    return res;   // retourner la valeur dépilée
}


/**
 * Fichier : node_queue.c (fichier gérant les nodes des queues)
 * Auteurs : Thomas BOTTALICO, Noe MOOS DEGOUTIN, Adrien RIVET
 * Version : 1.1
 */
