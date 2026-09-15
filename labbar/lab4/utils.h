#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


 typedef union 
 {
    /* data */
    int int_value;
    float float_value;
    char *string_value;
} answer_t;

typedef bool check_funk(char *str);
typedef answer_t convert_funk(char *str);

extern char* strdup(const char*);


void clear_input_buffer();
int read_string(char *buf, int buf_siz);

bool not_empty(char *str);

bool is_number(char *str);
answer_t ask_question(char *question, check_funk *check, convert_funk *convert);
int ask_questions_int(char *question);
char *ask_questions_string(char *question);



#endif