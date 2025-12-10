#include<stdio.h>
#include<unistd.h>

#include "web.h" // web.h contains str.h
#include "settings.h"

#define Write(__string) printf("%s", __string);
#define Writeln(__string) printf("%s\n", __string);
#define Printf(__format, ...) printf(__format, ##__VA_ARGS__);
#define Int(__int_value) printf("%d", __int_value);

int parse_template(String template_name, String content_type) {
    FILE *template_file = fopen(stringcat(TEMPLATE_DIR, template_name), "r");
    FILE *parse_template = fopen(stringcat(TEMPLATE_OUTPUT_DIR, stringcat(template_name, ".h")), "w");
    // printf("%s\n", stringcat(TEMPLATE_OUTPUT_DIR, stringcat(template_name, ".h")));
    int character, next_char;
    int code_flag = 0;
    int text_flag = 0;
    int pvar_flag = 0;
    if(template_file == NULL || parse_template == NULL) {
        printf("Error<%s>: File Not Open",__FILE__);
        return 1;
    }
    fprintf(parse_template, "Writeln(\"Content-Type: %s \\n\\n \")\n\n", content_type);
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
            if(character == '$' && !pvar_flag) {
                pvar_flag = 1;
                fprintf(parse_template, "getParam(\"");
                continue;
            } else if(character == '$' && pvar_flag) {
                pvar_flag = 0;
                fprintf(parse_template, "\") ");
                continue;
            }
            fputc(character, parse_template);
        } // HTML Text
        else{
            if(!text_flag){
                fprintf(parse_template, "Write(\"");
                text_flag = 1;
            }
            if(character == '\n') {
                fprintf(parse_template, "\")\nWrite(\" ");
                // fprintf(parse_template, "  \"  \n  \" ");
                continue;
            } else if(character == '"') {
                putc('\\', parse_template);
            }
            fputc(character, parse_template);
        }
    }
    if(text_flag) {
        fprintf(parse_template, "\" )\n" );
        text_flag = 0;
    }
    clear_gc(-1);
    fclose(template_file);
    fclose(parse_template);
    return 0;
}