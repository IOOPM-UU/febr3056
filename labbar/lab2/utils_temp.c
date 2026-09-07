#include <stdio.h>
#include <string.h>

int read_string(char *buf, int buf_siz) {
 

    //precon: buf siz måste vara >= 1 och kan inte börja med siffror
    int total_read = 0;
    int result;
    scanf("%d", &result);
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

int main(void)
{
    int buf_siz = 255;
    int read = 0;
    char buf[buf_siz];

    puts("Läs in en sträng:");
    read = read_string(buf, buf_siz);
    printf("'%s' (%d tecken)\n", buf, read);

    puts("Läs in en sträng till:");
    read = read_string(buf, buf_siz);
    printf("'%s' (%d tecken)\n", buf, read);

    return 0;
}