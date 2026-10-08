#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../iterator.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"


/// @brief Process a single word, updating its frequency
/// @param word the word to process
/// @param ht a hash table containing the frequencies of the words found so far
void process_word(char *word, ioopm_hash_table_t *ht) {
	// TODO what error handling could be needed talk to Felix
  	int w_freq = 0;
	bool word_not_found = !ioopm_hash_table_lookup(ht, word, &w_freq);
	

	if (word_not_found) {
		//char *pWord = calloc(1, sizeof(word));
		//char *tmp = pWord;
		//pWord = strdup(word);
		ioopm_hash_table_insert(ht, strdup(word)/*pWord*/, 1);
		//free(pWord);
		//free(tmp);
	} 

	
	else {
		//char *pWord = calloc(1, sizeof(word));
		//char *tmp = pWord;
		//pWord = strdup(word);
		ioopm_hash_table_insert(ht, strdup(word)/*pWord*/, w_freq + 1);
		//free(pWord);
		//free(tmp);
	}

}

/// @brief Process a single file, updating the frequencies of its words
/// @param filename the name of the file to process
/// @param ht a hash table containing the frequencies of the words found so far
void process_file(char *filename, ioopm_hash_table_t *ht) {
  	FILE *f = fopen(filename, "r");
	// =============================added lines=============================
	char *buf = NULL;
	size_t len = 0;
	//======================================================================
	while (/*true*/getline(&buf, &len, f) != -1) {//getline returns -1 on encountering EOF or an error.
		//buf = NULL;// erases buf and f's up len.
		//len = 0;// erases buf and f's up len.
		//getline(&buf, &len, f);
		for (char *word = strtok(buf, Delimiters);
		     word && *word;
		     word = strtok(NULL, Delimiters)) {
			
            process_word(word, ht);
		}
		free(buf);
	}
	//free(buf); // =============================added line=============================
	fclose(f);
}
/// @brief A word together with its frequency
struct freq_word {
	char *word;
	int freq;
};

/// @brief Compare the frequency of two freq_words through pointers to them
/// @param p1 the first freq_word
/// @param p2 the second freq_word
/// @return a number @n@:
///     @n@ > 0  if @p1@'s frequency is higher than @p2@'s
///     @n@ < 0  if @p1@'s frequency is lower than @p2@'s
///     @n@ == 0 if @p1@'s frequency is equal to @p2@'s
static int cmp_freq_words(const void *p1, const void *p2) {
	  const struct freq_word *w1 = p1;
	  const struct freq_word *w2 = p2;

	  return w1->freq - w2->freq;
}

/// @brief Like @cmp_freq_words@ but with the comparison result reversed
static int cmp_freq_words_reverse(const void *p1, const void *p2) {
  	return -cmp_freq_words(p1, p2);
}

/// @brief Sort an array of @freq_word@s in descending frequency order
/// @param words the array to be sorted
/// @param no_words the number of elements in the array
void sort_freq_words(struct freq_word words[], size_t no_words) {
  	qsort(words, no_words, sizeof(struct freq_word), cmp_freq_words_reverse);
}

int main(int argc, char *argv[]){
	if (argc < 2) {
		printf("Usage: %s file1 ... filen", argv[0]);
		return 1;
	}
//1. Create an empty hash table
  	ioopm_hash_table_t *ht = ioopm_hash_table_create();

// 2. For each file argument, read each word in the file 
	// 1. If the word is not in the hash table, put it there, and give it the value 1
	// 2. If the word is in the hash table, Increment its current value by 1	
	for (int i = 1; i < argc; ++i) {
		process_file(argv[i], ht);
	}

// 3. Get all hash table keys... 
  	int ht_size = ioopm_hash_table_size(ht);
  	struct freq_word freq_words[ht_size]; // Aray where each element is a <struct freq_word> i.e a word and its frequency in a struct.
	ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht); 
 	
	// Iterate over hash table to dump its struct freq_words into array above.
	for (int i = 0; i < ht_size; ++i, ioopm_hash_table_iterator_advance(it)) {
		struct freq_word struct_to_insert = {.word = ioopm_hash_table_iterator_current_key(it), .freq = ioopm_hash_table_iterator_current_value(it)};
		freq_words[i] = struct_to_insert;
	}
//  ...and sort according to frequency.
  	sort_freq_words(freq_words, ht_size);

//4. For each key, in the sorted order
	//1. Print the key and its frequency
	for (int i = 0; i < ht_size; ++i) {
		printf("%s: %d\n", freq_words[i].word, freq_words[i].freq);
  	}

// 5. Tear down the hash table, free all resources, close all files
	ioopm_hash_table_iterator_destroy(it);
	ioopm_hash_table_destroy(ht);
}
