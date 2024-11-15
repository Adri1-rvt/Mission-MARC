/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#include <stdio.h>
#include "map.h"
#include "tree.h"
#include "interface.h"


/**==========FONCTION PRINCIPALE DU PROJET==========*/
int main() {

    // start_menu();

    #if defined(_WIN32) || defined(_WIN64)
        t_map map = createMapFromFile("..\\maps\\example1.map");
    #elif defined(__APPLE__) || defined(__MACH__)
        t_map map = createMapFromFile("../maps/example1.map");
    #else
        printf("Système d'exploitation non reconnu.\n");
    #endif

    printf("Carte d'exemple de dimensions %d x %d :\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++) printf("%d ", map.soils[i][j]);
        printf("\n");
    }

    printf("\n");
    printf("Carte d'exemple avec les couts associes :\n");
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("Dessin de la carte d'exemple :\n");
    displayMap(map);


    t_move* test;
    test = random_possibilities();

    for (int j = 0; j < NB_possibilities; j++)
    printf("%s   ", getMoveAsString(test[j]));
    printf("\n");

    t_localisation loc = loc_init(2, 6, NORTH);

    t_node* node = NULL;
    node = create_all_Node(NB_possibilities, 0, test, loc, map);

    //printf("Min = %d\n", search_min(node));

    int path[node->depth];
    int path_length = 0;
    int min_val = path_min(node,path,&path_length);
    printf("Feuille de valeur minimale = %d\n", min_val);
    for (int i = 0; i < path_length; i++){
        printf("%d ",path[i]);
        if (i != path_length - 1) printf("-> ");
    }
    free(node);
    free(test);

    return 0;
}