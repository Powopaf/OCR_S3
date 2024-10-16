#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert(const char* path) {    //path MUST end with the impg.png file
    
    char cmd[2048];
    sprintf(cmd, "magick \"%s\" output/img.bmp", path);
    system(cmd);

    /*
    char prefix[] = "magick ";     //part before the path in command
    char suffix[] = " output/img.bmp";     //part after the path in command can add -alpha
                                    //off
    // Use sizeof to allow for null char at end.
    char *convert = malloc(sizeof(prefix) + strlen(path) + sizeof(suffix));
    if (convert != NULL) {
        //building command
        strcpy(convert, prefix);
        strcat(convert, path);
        strcat(convert, suffix);
        printf("command: %s :end\n", convert);
        system(convert);	//lauch command
        free(convert);
    }
    */
}