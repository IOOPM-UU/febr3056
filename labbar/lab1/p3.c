#include <stdio.h>

int total = 0;
int asterisk(int n) {
for (int i = 1; i <= n; i = i + 1) {
        printf("*");
        total = total + 1;
    }
}
int main(void) {
    for (int i = 1; i <= 10; i = i + 1) {
        //printf("%d\n", i);
        asterisk(i);
        puts("");
    }

    printf("Total: %d\n", total);
    return 0;
}

