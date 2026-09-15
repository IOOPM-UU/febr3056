#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
int string_length (char *str) {
    int counter = 0;
    if (str[0] == '\0')
    {
        return 0;
    } else {
        do
        {
            counter += 1;
        } while (str[counter] != '\0');
    }
    return counter;
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
    int length = string_length(str);
    //str[length] = '\n';
    //str[length + 1] = '\0';
    print(str);
    print("\n");
}


int main(int argc, char *argv[]) {
    if (argc < 2)
    {
        printf("Usage: %s words or string", argv[0]);
    } else {
        for (int i = 1; i < argc; i++)
        {
            int expected = strlen(argv[i]);
            int actual = string_length(argv[i]);
            printf("strlen(\"%s\") = %d\t\tstring_length(\"%s\") = %d\n", argv[i], expected, argv[i], actual);
        }
    }
    print(argv[1]);

    println(argv[1]);

    puts(argv[1]);
    //puts(argv[1]);

    return 0;
}