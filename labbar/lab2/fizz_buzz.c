#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void print_number(int num) {
    if (num % 3 == 0 && num % 5 == 0) {
        printf("Fizz Buzz");
    } else if (num % 3 == 0)
    {
        printf("Fizz");
    } else if (num % 5 == 0)
    {
        printf("Buzz");
    } else {
        printf("%d", num);
    }
}

int main(int argc, char *argv[]) {
    int int_arg = atoi(argv[1]);

    for (int i = 1; i <= int_arg; ++i) {
        print_number(i);
        if (i != int_arg)
        {
            printf(", ");
        } else {
            puts("");
        }
    }
}