/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "path.h"
#include "interface.h"


/**==========FONCTION PRINCIPALE DU PROJET==========*/
int main() {

    start_menu();   // afficher notre magnifique logo

    // générer la map en vérifiant le système d'exploitation
    #if defined(_WIN32) || defined(_WIN64)   // si l'OS est windows
        t_map map = createMapFromFile("..\\maps\\example1.map");   // créer la map
    #elif defined(__APPLE__) || defined(__MACH__)   // si l'OS est mac (nul)
        t_map map = createMapFromFile("../maps/example1.map");   // créer la map
    #elif defined(__linux__)  // si l'OS est Linux   // si l'OS est une distribution Linux
        t_map map = createMapFromFile("../maps/example1.map");   // créer la map
    #else
        printf("Système d'exploitation incompatible.\n");
    #endif

    printf("Carte de dimensions %d x %d :\n", map.y_max, map.x_max);
    // parcourir le sol de la map pour l'afficher dans notre console
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++) printf("%d ", map.soils[i][j]);
        printf("\n");
    }
    printf("\n");

    // parcourir les coûts de la map pour l'afficher dans notre console
    printf("Carte d'exemple avec les couts associes :\n");
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Dessin de la carte d'exemple :\n");
    // afficher la map
    displayMap(map);
    printf("\n======================================================================================================\n\n");

    t_move* test;
    test = getRandomMoves(NB_possibilities);   // obtenir les 9 mouvements utilisables

    printf("Mouvements possibles : \n[ ");
    // afficher les mouvements utilisables
    for (int i = 0; i < NB_possibilities; i++){
        printf("%s ", getMoveAsString(test[i]));
        if (i < NB_possibilities - 1) printf("; ");
    }
    printf("]\n\n");

    // définir la position initiale
    t_localisation loc = loc_init(4, 6, NORTH);

    printf("Position initiale de MARC : (x: %d, y: %d, direction: NORTH)\n\n", loc.pos.x, loc.pos.y);

    // contruire notre arbre n-aire
    t_tree tree;   // créer une variable de type t_tree
    tree = create_tree(NB_possibilities, 0, INITIAL_POS, test, loc, map);   // créer notre arbre
    int min_val = search_min(tree);   // chercher la feuille de valeur minimale dans notre arbre
    printf("La valeur minimum sur laquelle MARC peut arriver = %d\n", min_val);

    p_node feuille_min = min_leaf(tree);    //La feuille de valeur minimale

    int nb_move;
    t_move* path = best_path(tree, &nb_move);   // trouver le meilleur chemin possible

    printf("\n");
    printf("Mouvements a effectuer pour arriver a la case de valeur minimale trouvee : \n[");
    // afficher les mouvements à effectuer dans l'ordre pour arriver à la case de valeur min
    for (int i = 0; i <= nb_move; i++)
    {
        printf("%s ", getMoveAsString(path[i]));
        if (i < nb_move) printf("; ");
    }
    printf("]\n");

    return 0;
}
