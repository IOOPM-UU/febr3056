#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
int check = 1;
int main(int argc, char *argv[]) {
    int checker(int n) {
        for (int i = 1; i < atoi(argv[1]); ++i) {
            if (i * n == atoi(argv[1])) {
                return false;
            }
        }
    }  
    if (argc != 2) {
        puts("Usage: ./a.out (number to check if prime)");
    }
    else {
        for (int i = 1; i < atoi(argv[1]); ++i) {
            if(checker(i) == false) {
                printf("%d is not prime.\n", atoi(argv[1]));
                check = 0;
                break;
            }
        }
        if (check == 1){
            printf("%d is prime!\n", atoi(argv[1]));
        }
    }
    return 0;

}

