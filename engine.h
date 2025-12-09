#include<stdio.h>
#include<unistd.h>

#include "str.h"
#include "settings.h"

#define Write(__string) dprintf(STDOUT_FILENO, "%s", __string);
#define Int(__int_value) dprintf(STDOUT_FILENO, "%d", __int_value);

int parse_template(String template_name) {
    FILE *template_file = fopen(stringcat(TEMPLATE_DIR, template_name), "r");
    FILE *parse_template = fopen(stringcat(TEMPLATE_OUTPUT_DIR, stringcat(template_name, ".h")), "w");
    // printf("%s\n", stringcat(TEMPLATE_OUTPUT_DIR, stringcat(template_name, ".h")));
    int character, next_char;
    int code_flag = 0;
    int text_flag = 0;
    if(template_file == NULL || parse_template == NULL) {
        printf("Error<%s>: File Not Open",__FILE__);
        return 1;
    }
    while((character = fgetc(template_file)) != EOF) {
        next_char = fgetc(template_file);
        ungetc(next_char, template_file);
        if(character == '<' && next_char == '#') {
            code_flag = 1;
            fgetc(template_file);
            continue;
        }
        else if(character == '#' && next_char == '>') {
            code_flag = 0;
            fgetc(template_file);
            continue;
        }
        // C code
        if(code_flag) {
            if(text_flag) {
                fprintf(parse_template, "\")\n" );
                text_flag = 0;
            }
            fputc(character, parse_template);
        } // HTML Text
        else{
            if(!text_flag){
                fprintf(parse_template, "Write(\"");
                text_flag = 1;
            }
            if(character == '\n') {
                fprintf(parse_template, "\")\nWrite(\"");
                continue;
            } else if(character == '"') {
                putc('\\', parse_template);
            }
            fputc(character, parse_template);
        }
    }
    if(text_flag) {
        fprintf(parse_template, "\")\n" );
        text_flag = 0;
    }
    clear_gc(-1);
    fclose(template_file);
    fclose(parse_template);
    return 0;
}