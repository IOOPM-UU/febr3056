#include <stdio.h>
#include <string.h>

int read_string(char *buf, int buf_siz) {

    //precon: buf siz måste vara >= 1 och kan inte börja med siffror
    int total_read = 0;
    int result;
    //fgets (buf, buf_siz, stdin);
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


int main(void) {
    char stringo[255];
    read_string(stringo, 100);
    printf("%s\n", stringo);
}