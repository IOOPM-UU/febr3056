#include <stdio.h>
#include <stdlib.h>
int total = 0;
int main(int argc, char *argv[]) {
    int asterisk(int n) {
        for (int i = 1; i <= atoi(argv[2]) * n; i = i + 1) {
            printf("*");
        }
        total = total + atoi(argv[2]) * n;
        return 0;
    }
    
    if (argc != 3) {
        puts("Usage: ./a.out rows growth");
    }
    else {
        for (int i = 1; i <= atoi(argv[1]); i = i + 1) {
            asterisk(i);
            printf("\n");
        }
    
        printf("Total: %d\n", total);
    }
    return 0;

}

