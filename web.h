#include <stdio.h>
#include <stdlib.h>
#ifdef __linux__
    #include <regex.h>
#endif
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

#ifdef __linux__
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
        if(length <= 0 ) {
            return NULL;
        }

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

#elif _WIN32
String getParam(String param) {
    String query_string= getenv("QUERY_STRING");

    if(query_string == NULL) {
        return NULL;
    }

    ull param_len = strlen(param);
    ull beg = 0, end = 0;
    String copy_query_string = query_string;
    int param_find = 0;
    while (*query_string != '\0') {
        if(param_find == 0 && *query_string == *param && !strncmp(query_string, param, param_len) && *(query_string+param_len) == '=') {         
            param_find = 1;
            beg = (query_string - copy_query_string) + param_len + 1;      
                        // printf(" beg : %c @ %d from %c to %c <br>", *(copy_query_string+beg), beg, *copy_query_string, *query_string);
      
        } else if(param_find && *query_string == '&') {
            end = (query_string - copy_query_string);
            param_find = 0;
            break;
        }
        query_string++;
    }
    if(param_find) {
        end = strlen(copy_query_string);
    }
    if(end - beg < 1) {
        return NULL;
    }
    // printf(" end = %d , beg = %d  <br>", end, beg);
    String result = STRING("", end - beg + 1);
    strncpy(result, copy_query_string + beg , end - beg);
    result[end-beg] = '\0';
    

    return result;
    

}
#endif

// String get_param(char **qs, String param) {

// }