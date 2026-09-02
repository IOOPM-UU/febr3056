#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/param.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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

int main(int argc, char *argv[]) {
    if (argc != 3 || MIN(atoi(argv[1]), atoi(argv[2])) <= 0) {
        puts("Usage: ./a.out (posite integer) (positive integer)");
        printf("%d\n", atoi(argv[1]));
    } else {
        int gcd(int a, int b) {
            if (a == b) {
                return a;
            } else if (a > b) {
                return gcd(a - b, b);
            }
            else if (a < b) {
                return gcd(a, b - a);
            };
        };
        int divider = gcd(atoi(argv[1]), atoi(argv[2]));
        printf("%d\n", divider);
    };
    return 0;
}