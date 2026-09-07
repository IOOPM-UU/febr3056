#include <stdio.h>
#include <string.h>

int main(void) {
    char *stringo;
    fgets(stringo, 10, stdin);
    printf("%s", stringo);
}