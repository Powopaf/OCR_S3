#include "is_ubuntu.h"
#include <stdio.h>
#include <string.h>

int is_ubuntu()
{
    FILE* file = fopen("/etc/os-release","r");

    if (file == NULL) {
        perror("Impossible d'ouvrir /etc/os-release");
        return 0; // Fichier introuvable ou erreur d'accès
    }

    char line[256];
    int is_ubuntu = 0;

    while(fgets(line, sizeof(line), file) != NULL)
    {
        if(strncmp(line, "ID=ubuntu", 9) == 0)
        {
            is_ubuntu = 1;
            break;
        }
    }
    fclose(file);
    return is_ubuntu;
}

