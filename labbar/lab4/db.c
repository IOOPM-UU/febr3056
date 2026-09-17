#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/param.h> 
#include <ctype.h>
#include <string.h>

struct item
{
    char *name;
    char *desc;
    int price;
    char *shelf;
};
typedef struct item item_t;

void print_item(item_t *item) {
    printf("Name: %s\n", item->name);
    printf("Description: %s\n", item->desc);
    char *price_dec = "";
    if (item->price % 100 >= 10)
    {
        printf("Price: %d.%d SEK\n", item->price / 100, item->price % 100);
    } else {
        printf("Price: %d.0%d SEK\n", item->price / 100, item->price % 100);
    }
    
    printf("Shelf: %s\n", item->shelf);
}

item_t make_item(char *name, char *desc, int price, char *shelf) {
    item_t result = {.name = name, .desc = desc, .price = price, .shelf = shelf};
    return result;
}

bool is_shelf(char *str) {
    int state = 1;
    int length = strlen(str);
    if (length == 1 || length == 0)
    {
        state = 0;
    }
    
    for (int i = 0; i < length; ++i) {
        if ((i == 0 && !isalpha(str[i])) || (i != 0 && !isdigit(str[i]))) {
            state = 0;
        } 
    };
    return state;
}

char *ask_questions_shelf(char *question) {
    return ask_question(question, is_shelf, (convert_funk *) strdup).string_value;
}
item_t input_item() {
    char *name = ask_questions_string("Input item name:\n");
    char *desc = ask_questions_string("Input item description:\n");
    int price = abs(ask_questions_int("Input item price (SEK):\n"));
    char *shelf = ask_questions_shelf("Input item shelf:\n");
    return make_item(name, desc, price, shelf);
}
void print(char *str) {
    //int counter = 0;
    if (*str != '\0')
    {
        do
        {
            putchar(*str);
            ++str;
        } while (*str != '\0');
    }
}

int write_to(char *src, char *dest, int start) {
    //int counter = 0;
    char *init = dest;
    dest += start;
    //if (*src != '\0') {
        
    while (*src != '\0')
        {
            *dest = *src;
            ++src;
            ++dest;
        };
    //}
    return dest - init;
}
char *magick(char *array1[], char *array2[], char *array3[], int size) {
    char buf[255];
    char *tmp = buf;
    int counter = 0;
    
    char *random1 = array1[rand() % size];
    counter = write_to(random1, tmp, counter);

    buf[counter] = '-';
    counter += 1;

    char *random2 = array2[rand() % size];
    counter = write_to(random2, tmp, counter);
    
    buf[counter] = ' ';
    counter += 1;

    char *random3 = array3[rand() % size];
    counter = write_to(random3, tmp, counter);

    buf[counter] = '\0';
    return strdup(buf);
}

void list_db(item_t *items, int no_items) {
    for (int i = 0; i < no_items; ++i) {
        printf("%d. %s\n", i + 1, items[i].name);
    }
}

void edit_db(item_t *items) {
    int item_id = ask_questions_int("Wich item do you whish to edit?\n");
    if (item_id > 16 || item_id < 1) {
        printf("Out of bounds.");
    }

    print_item(&items[item_id - 1]);
    items[item_id - 1] = input_item();
}

char *print_menu() {
    return ( 
        "[L]ägga till en vara\n[T]a bort en vara\n[R]edigera en vara\n"
        "Ån[g]ra senaste ändringen\nLista [h]ela varukatalogen\n[A]vsluta\n");
}

bool valid_input_menu(char *c) {
    int state = 1;
    if (strlen(c) != 1 || !strpbrk("LlTtRrGgHhAa", c)) {
        state = 0;
    }
    return state;
}
char *identity(char *str) {
    return str;
}

char ask_questions_menu(char *question) {
    char result = *ask_question(question, valid_input_menu, (convert_funk *) identity).string_value;
    return (char) toupper(result);
}

void add_item_to_db(item_t *items, int *no_items) {
    items[*no_items] = input_item();
    *no_items += 1;
}

void remove_item_from_db(item_t *items, int *no_items) {
    list_db(items, *no_items);
    int item_id = ask_questions_int("Which item do you wish to remove?\n");
    if (item_id >= 1 && item_id <= *no_items)
    {
        /* code */
        for (int i = item_id - 1; i < *no_items - 1; ++i) {
            items[i] = items[i + 1];
        }
        *no_items -= 1;
    } else {
        printf("Item ID out of bounds\n");
    }
    //int variabeln_jag_vill_ha_eller_variabelnamnet;
}

void event_loop(item_t *items, int no_items) {
    int input = 0;
    do
    {
        /* code */
        input = ask_questions_menu(print_menu());
        if (input == 'L' || input == 'l') {
            add_item_to_db(items, &no_items);
        } else if (input == 'T')
        {
            /* code */
            remove_item_from_db(items, &no_items);
        } else if (input == 'R')
        {
            /* code */
            edit_db(items);
        } else if (input == 'G')
        {
            printf("Ännu ej implementerad!\n");
        } else if (input == 'H')
        {
            list_db(items, no_items);
        } 
    } while (input != 'A');
    

}

int main(int argc, char *argv[])
{
  char *array1[] = { "hej", "boj", "ja" }; 
  char *array2[] = { "upp", "ner", "vänster" };
  char *array3[] = { "norr", "öst", "söder" }; 

  if (argc < 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    item_t db[16]; // Array med plats för 16 varor
    int db_siz = 0; // Antalet varor i arrayen just nu

    int items = atoi(argv[1]); // Antalet varor som skall skapas

    if (items > 0 && items <= 16)
    {
      for (int i = 0; i < items; ++i)
      {
        // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
        /*
        */
        item_t item = input_item();
        db[db_siz] = item;
        ++db_siz;
        
      }
    }
    else
    {
      puts("Sorry, must have [1-16] items in database.");
      return 1; // Avslutar programmet!
    }

    for (int i = db_siz; i < 16; ++i)
      {
        char *name = magick(array1, array2, array3, 3); 
        char *desc = magick(array1, array2, array3, 3); 
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, price, strdup(shelf));

        db[db_siz] = item;
        ++db_siz;
      }

     // Skriv ut innehållet
     /*
     for (int i = 0; i < db_siz; ++i)
     {
        print_item(&db[i]);
    }
    */

    //edit_db(db);
    list_db(db, db_siz);
     
    event_loop(db, db_siz);
    //printf(print_menu());

  }
  return 0;
}