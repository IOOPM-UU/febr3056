#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int main(void) {
    //int buf_siz = 255;
    //char buf[buf_siz];
    
    int guess = 0;
    int total_guesses = 15;
    int guesses_made = 0;
    

    int true_number = 0;
    true_number = rand() % 1000;


    char *name = ask_questions_string("Skriv in dit namn: ");
    //char *name = "Felix";
    do {
        if (guesses_made == 0)
        {
            printf("Du %s, jag tänker på ett tal, kan du gissa vilket?\n", name);
            guess = ask_questions_int("");
        } else {
            if (guess > true_number)
            {
                guess = ask_questions_int("Lägre!\n");
            } else {
                //printf("\n%d\n", guess);
                guess = ask_questions_int("Högre!\n");
            }
            if (guess == 1337)
            {
                break;
            }
            
            //guess = ask_questions_int("Gissa igen.");
        }
        guesses_made += 1;
        
    }
    while (guess != true_number && guesses_made < total_guesses);
    if (guess == true_number) {
        printf("Grattis! %d var siffran jag tänkte på! Det tog dig %d gissningar.\n", guess, guesses_made);
        return 0;
    } else {
        printf("Det var den sista gissningen! Rätt svar var %d\n", true_number);
        return 0;
    }
}