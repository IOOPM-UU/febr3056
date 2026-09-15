#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

void clear_input_buffer() {
    int c;
    do {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
}
int read_string(char *buf, int buf_siz) {

    //precon: buf siz måste vara >= 1 och kan inte börja med siffror
    int total_read = 0;
    int c;

    while (total_read < (buf_siz - 1) && c != '\n')
    {
        c = getchar();
        buf[total_read] = c;
        total_read += 1;
    } 
    if (c == '\n') {
        total_read -= 1;
    }

    buf[total_read] = '\0';
    return total_read;
}


bool not_empty(char *str) {
    return strlen(str) > 0;
}
bool is_number(char *str) {
    int state = 1;
    int length = strlen(str);
    for (int i = 0; i < length; ++i) {
        if (!isdigit(str[i])) {
            state = 0;
        }
    };
    return state;
}
answer_t ask_question(char *question, check_funk *check, convert_funk *convert) {
    int buf_siz = 254;
    char buf[buf_siz];

    do
    {
        printf("%s", question);
        read_string(buf, buf_siz);
    
    } while (!check(buf));
    //answer_t result = convert(buf);


    return convert(buf);
}
int ask_questions_int(char *question) {
    answer_t answer = ask_question(question, is_number, (convert_funk *) atoi);
    return answer.int_value;
}

char *ask_questions_string(char *question) {
    return ask_question(question, not_empty, (convert_funk *) strdup).string_value;
}



/*
char *ask_questions_string(char *question, char *buf, int buf_siz) {
    //clear_input_buffer();
     // <-- bufferstorlek 255
     int str_len = 0;
     
     bool accept_empty = true;
     
     if (accept_empty)
     {
        printf("%s\n", question);
        read_string(buf, buf_siz);
    }
    else{
        do
        {
            printf("%s\n", question);
            str_len = read_string(buf, buf_siz);
            //clear_input_buffer();
            //putchar('\n');
        } while (str_len == 0);
    }
    
    return strdup(buf);
}


int ask_question_int(char *question) {
    int result = 0;
    int conversions = 0;
    do {
        printf("%s\n", question);
        conversions = scanf("%d", &result);
        clear_input_buffer();
        putchar('\n');
    }
    while (conversions < 1);
    return result;
}

void print(char *str) {
    int counter = 0;
    if (str[0] != '\0')
    {
        do
        {
            putchar(str[counter]);
            counter += 1;
        } while (str[counter] != '\0');
    }
}

void println (char *str) {
    int length = strlen(str);
    //str[length] = '\n';
    //str[length + 1] = '\0';
    print(str);
    print("\n");
}
    */