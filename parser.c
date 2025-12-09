#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#include "engine.h" 

void traverse_directory(const char *dirname) {
    DIR *dp;
    struct dirent *entry;

    dp = opendir(dirname);
    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char filepath[512]; // Adjust size as needed
        snprintf(filepath, sizeof(filepath), "%s/%s", dirname, entry->d_name);

        if (entry->d_type == DT_DIR) {
            // Recursively traverse subdirectories
            traverse_directory(filepath);
        } else if (entry->d_type == DT_REG) {
            // Process regular files
            parse_template(entry->d_name);
        }
    }
    closedir(dp);
}

int main(int argc, char *argv[]) {
    // Check if at least one argument (besides the program name) is provided
    if (argc > 1) {
        traverse_directory(argv[1]);
    } else {
        printf("No fiel path is provided taking default: ./template\n");
        traverse_directory(TEMPLATE_DIR);
    }
    return 0;
}