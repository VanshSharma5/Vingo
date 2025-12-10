#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "str.h"

String getMethod() {
    String method = getenv("REQUEST_METHOD");

    return method;
}

int isPress(String param) {
    if(param == NULL) {
        return 0;
    }
    return 1;
}

String postParam(String param) {
    // String content_length = getenv("CONTENT_LENGTH");
    // if(!content_length) {
    //     return NULL;
    // }

    // int len = parseInt(content_length);
}

String getParam(String param) {
    String query_string= getenv("QUERY_STRING");
    // if(query_string=NULL) {
    //     return postParam(param);
    // }
    // printf(query_string);

    regex_t regex;
    int reti = regcomp(&regex, stringcat(param, "=([^&]+)"), REG_EXTENDED);
    if (reti) {
        printf("Error<%s>: regex not composed\n", __FILE__);    // Handle error
    }

    regmatch_t pmatch[2]; // One for the full match, one for the capturing group
    reti = regexec(&regex, query_string, 2, pmatch, 0);

    if (!reti) {
        int start = pmatch[1].rm_so; // Start offset of the captured group
        int end = pmatch[1].rm_eo;   // End offset of the captured group
        int length = end - start;

        // Allocate memory for the extracted value and copy it
        // char *param_value = (char *)malloc(length + 1);
        String param_value = STRING("", length);
        strncpy(param_value, query_string + start, length);
        param_value[length] = '\0'; // Null-terminate the string

        replaceChar(param_value, '+', ' ');

        // Use param_value
        // printf("Parameter value: %s\n", param_value);

        return param_value;
    } else if (reti == REG_NOMATCH) {
        return NULL; // No match
    } else {
        return NULL;
        // Handle error
    }
    return query_string;
}
// String get_param(char **qs, String param) {

// }