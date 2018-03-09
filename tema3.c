/* NICOLESCU Daniel-Marian - 314CB */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Trie.h"
#include "Functions.h"

#define MAX 5

// trie-ul este implementat folosind numai liste
// trie->child este fiul direct al nodului trie
// trie->next este nodul din dreapta nodului trie

// *
// |
// a - - - b
// |       |
// b - n   a
// |   |   |
// a   a   n

// cuvinte: aba, ana, ban

int main(int argc, char *argv[])
{
	ATrie trie;
	size_t nr_comm, i, k;
	char comm[21];
	char c;
	char *word;
	char *word_aux;
	size_t len = MAX;
	size_t check;

	if(argc != 3)
	{
		printf("Not enough arguments");
		return 0;
	}

	FILE *input = fopen(argv[1], "r");

	if(!input)
	{
		printf("No such input file");
		return -1;
	}

	FILE *output = fopen(argv[2], "w");

	fscanf(input, "%zu", &nr_comm);

	// initializare trie prin adaugarea nodului radacina
	trie = InitNode('*');

	if(!trie) 
		return -1;

	for(i = 0; i < nr_comm; i++)
	{
		fscanf(input, "%s", comm);

		// citire cuvant
		check = ReadWord(&word, input);

		if(check == 0)
		{
			free(trie);
			return -1;
		}

		if(!strcmp(comm, "add"))
		{
			check = AddWord(trie, word);

			if(check == 0)
			{
				free(trie);
				return -1;
			}			
		}

		if(!strcmp(comm, "remove"))
		{
			ATrie ant = NULL;
			size_t p = 0;
			size_t q = 0;
			RemoveWord(ant, trie, word, p, &q);	
		}

		if(!strcmp(comm, "find"))
		{
			FindWord(trie, word, output);
		}

		if(!strcmp(comm, "find_longest_prefix"))
		{
			FindLongestPref(trie, word, output);
		}

		if(!strcmp(comm, "find_all_with_prefix"))
		{
			FindAllWithPref(trie, word, output);
		}

		if(!strcmp(comm, "mean_length"))
		{
			MeanLength(trie, word, output);
		}

		free(word);
	}

	// eliberare trie din memorie
	FreeTrie(trie);

	fclose(input);
	fclose(output);

	return 0;
}