
#include "hash_iterator.h"
#include "iterator.h"

struct freq_pair {
    int freq;
    char *key;
};
typedef struct freq_pair freq_pair_t;

struct hash_table_iterator
{
  ioopm_hash_table_t *ht;
  int current_bucket;
  entry_t *current_entry;
};


int compare_pairs(const void *pair1, const void *pair2) {
    freq_pair_t *p1 = pair1;
    freq_pair_t *p2 = pair2;

    if (p1->freq < p2->freq) {
        return -1;
    } else if (p1->freq == p2->freq)
    {
        return 0;
    } else {
        return 1;
    }
    
}


int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Usage: any number of paths to text files, each separated by a space\n");
    } else {

        //FIXME: according to studium, we prob want to use strdup somewhere.  
        fflush(stdout);

        printf("before create\n"); //debug
        fflush(stdout);

        ioopm_hash_table_t *ht = ioopm_hash_table_create();

        printf("after create\n"); //debug
        fflush(stdout);
        for (int i = 1; i < argc; i++) {
            //FIXME: cannot currently actually find any files, only create

            printf("before open\n"); //debug
            FILE *file = fopen(argv[i], "w+");

            printf("after open\n"); //debug
            if (file == NULL) {
                printf("FAIL\n");
            }

            printf("before print\n"); //debug
            fprintf(file, "hej hej då då då");
            printf("after print\n"); //debug
            char *result = "";
            result = (char *) getline(&result, 0, file);
            
            char *token = strtok(result, " ");

            while (token != NULL) {
                int get_value = 0;
                //lookup will set get_value to 0 if token is not in table, thus allowing this code to
                //both initiate and increment entries.
                ioopm_hash_table_lookup(ht, token, &get_value);        
                ioopm_hash_table_insert(ht, token, get_value + 1);

                token = strtok(NULL, " ");
            }
            fclose(file);
        }

        ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);


        //for each entry in ht, insert that entry into freqpairs
        //for loop, since we know how many times we wanna do it
        //so like: entry.freq = currententry-value
        //entry.key = current.key
        int table_size = ioopm_hash_table_size(ht); 

        freq_pair_t *freq_pairs[table_size];
        for (int i = 0; i < table_size; i++) {
            int freq = it->current_entry->value;
            char *key = it->current_entry->key;
            freq_pair_t entry = {freq, key};
            freq_pairs[i] = &entry;
            ioopm_hash_table_iterator_advance(it);
        }
        
        qsort(freq_pairs, table_size, table_size * sizeof(freq_pair_t), compare_pairs);

        for (int i = 0; i < table_size; i++) {
        printf("%d, %s\n", freq_pairs[i]->freq, freq_pairs[i]->key);
        }

    }
}

    /*
    while not at end(
    
struct {
    int,
    char
} freq-pair

sort an array of type freq-pair by the ints, possible? yes!


    insert current.key into array
    insert current.value into array
    index++
    advance


    )
    
    
    
    qsort();
    */


    //i wonder if there exists a way to save into a variable the way an array was reordered
    //by a sorting function, then apply that same reordering to another.
    //for example, if sort was done on [5,1,3,2,4], save the fact that [0] moved to [4], [3] to [1], and so on.