#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define catcat(str1, str2) #str1 #str2

#define MAXGARBAGE 1024

typedef char* String;
typedef unsigned long long ull;

String STRING(const char *__string, ull size) {
    String str;
    if(size == 0) {
        size = strlen(__string) + 1;
    }
    void* temp = malloc(sizeof(char)*size);
    if(temp == NULL) {
        printf("Error<%s>: STRING is Not Initilize", __FILE__);
        return NULL;
    }
    strcpy(temp, __string);
    str = (char*)temp;

    return str;
}

void* GARBAGE[MAXGARBAGE];
ull gtop = -1;

void clear_gc(int offset) {
    while(offset != 0 && gtop != -1) {
        free(GARBAGE[gtop--]);
    }
}

String stringcat(String str1, String str2) {
    ull size = strlen(str1) + strlen(str2) + 1;
    String str = STRING("", size );
    strcpy(str, str1);
    strcat(str, str2);

    GARBAGE[++gtop] = (void*)str;

    return str;
}


void replaceChar(String str, char oldChar, char newChar) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == oldChar) {
            str[i] = newChar;
        }
    }
}

int parseInt(char str[]) {
    int res = 0;
    int i = 0;
    int sign = 1;

    // Handle negative numbers
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }

    // Convert digits
    for (; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            res = res * 10 + (str[i] - '0');
        } else {
            // Handle non-numeric characters (e.g., return 0 or an error code)
            return 0; 
        }
    }
    return sign * res;
}