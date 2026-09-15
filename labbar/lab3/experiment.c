//#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

extern char* strdup(const char*);
typedef union 
{
    /* data */
    int int_value;
    float float_value;
    char *string_value;
} answer_t;

typedef bool check_funk(char *str);
typedef answer_t convert_funk(char *str);

//Checker-functions

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

//Convert-functions

answer_t make_double(char *str) {
    /*
    answer_t result;
    result.float_value = atof(str);
    return result;
    */
   return (answer_t) {.float_value = atof(str)};
}
//

answer_t ask_question(char *question, check_funk *check, convert_funk *convert) {
    int buf_siz = 25;
    char buf[buf_siz];

    do
    {
        printf("%s", question);
        read_string(buf, buf_siz);
    
    } while (!check(buf));
    return convert(buf);
}

int ask_questions_int(char *question) {
    answer_t answer = ask_question(question, is_number, (convert_funk *) atoi);
    return answer.int_value;
}

char *ask_questions_string(char *question) {
    return ask_question(question, not_empty, (convert_funk *) strdup).string_value;
}


int main(void) {
    int buf_siz = 25;
    char buf[buf_siz];    
}