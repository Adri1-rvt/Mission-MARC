//
// Created by adrie on 13/11/2024.
//

/**==========DIRECTIVES DU PREPROCESSEUR==========*/
#include "interface.h"


/**==========FONCTIONS==========*/
void start_menu() {

    // afficher le logo en caractères ascii de notre projet (parce qu'on est trop stylé !)
    printf("        .__              .__                                                \n"
           "  _____ |__| ______ _____|__| ____   ____       _____ _____ _______   ____  \n"
           " /     \\|  |/  ___//  ___/  |/  _ \\ /    \\     /     \\\\__  \\\\_  __ \\_/ ___\\ \n"
           "|  Y Y  \\  |\\___ \\ \\___ \\|  (  <_> )   |  \\   |  Y Y  \\/ __ \\|  | \\/\\  \\___ \n"
           "|__|_|  /__/____  >____  >__|\\____/|___|  /   |__|_|  (____  /__|    \\___  >\n"
           "      \\/        \\/     \\/               \\/          \\/     \\/            \\/ \n\n");

    // afficher les informations importantes du projet
    printf("\t==============================================================================================\n"
           "\tAuteurs         : Thomas B, Noe M, Adrien R                    |                             |\n"
           "\tVersion         : v1.1                                         |           Appuyez           |\n"
           "\tDerniere maj    : 13-11-2024                                   |             Sur             |\n"
           "\tLien Github     : https://github.com/Adri1-rvt/---             |            Enter            |\n"
           "\t===============================================================|            Pour             |\n"
           "\tBienvenue sur Mission MARC, le projet C qui va vous            |           Lancer            |\n"
           "\tpermettre de diriger MARC sur mars !                           |                             |\n"
           "\t==============================================================================================\n\n\n");

    // mettre en pause le programme tant que l'utilisateur ne l'a pas lancé
    getchar();
}


/**
 * Fichier : interface.c (fichier gérant l'affichage de l'interface console)
 * Auteurs : Thomas BOTTALICO, Noe MOOS DEGOUTIN, Adrien RIVET
 * Version : 1.1
 */