#include <stdio.h>
#include <string.h>

int read_string(char *buf, int buf_siz) {
 

    //precon: buf siz måste vara >= 1 och kan inte börja med siffror
    int total_read = 0;
    int result;
        
    fgets(buf, buf_siz, stdin);
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

void clear_input_buffer() {
    int c;
    do {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
}

char *ask_questions_string(char *question) {
    //clear_input_buffer();
    char result[255]; // <-- bufferstorlek 255
    int str_len = 0;
    do
    {
        printf("%s\n", question);
        str_len = read_string(result, 255);
    } while (str_len == 0);
    
    return strdup(result);
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

int main(void) {
    int tal;
    char *ord;
    tal = ask_question_int("Första talet: ");
    printf("Du skrev in %d\n", tal);

    tal = ask_question_int("Andra talet: ");
    printf("Du skrev in %d\n", tal);

    ord = ask_questions_string("Första ordet: ");
    printf("Du skrev in %s\n", ord);
}


