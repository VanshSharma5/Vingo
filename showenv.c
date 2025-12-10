#include <stdio.h>
#include <stdlib.h>
#include "web.h"

char** main(int argc, char **argv, char **env) {
    printf("Content-Type: text/html\n\n");
    while(*env) {
        printf("%s\n<br>\n", *env);
        env++;
    }
    // printf(getParam("name"));
    // getParam("name");
    return 0;
}