/* NICOLESCU Daniel-Marian - 314CB */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Trie.h"

#define MAX 5

// citire cuvant din fisier
size_t ReadWord(char **word, FILE *input)
{
	size_t len = MAX;
	char *word_aux;
	size_t i = 0;
	char c;

	*word = (char*)malloc(len * sizeof(char));

	if(!(*word)) 
		return 0;

	fscanf(input, "%c", &c);

	if(c != '\n' && c != '\r')
	{
		while(fscanf(input, "%c", &c) == 1 && c != '\n' && c != '\r')
		{
			// realocare in cazul in care numarul curent de caractere citite
			// este egal cu numarul de elemente alocate pentru cuvant
			if(i == len-1)
			{
				len += MAX;
				word_aux = (char*)realloc(*word, len * sizeof(char));

				if(!word_aux)
				{
					free(*word);
					return 0;
				}

				*word = word_aux;
			}

			(*word)[i] = c;

			++i;
		}
	}

	// adaugare null terminator
	(*word)[i] = '\0';

	return 1;
}

// initializare nod cu caracterul character
ATrie InitNode(char character)
{
	ATrie trie = (ATrie)malloc(sizeof(TTrie));

	if(!trie) return NULL;

	trie->character = character;
	trie->is_word = 0;
	trie->child = NULL;
	trie->next = NULL;

	return trie;
}

// adaugare cuvant in trie
// adaugarea se face in ordine alfabetica
size_t AddWord(ATrie trie, char *word)
{
	size_t len = strlen(word);
	size_t i, ok;
	ATrie aux, ant, parent;
	ATrie copy = trie;

	// parcurgere trie
	for(i = 0; i < len; i++)
	{
		// parent este nodul anterior care este folosit
		// pentru a lega un nod nou creat de trie

		// parcurgere in adancime
		parent = trie;
		trie = trie->child;

		// daca nu exista nod, atunci el este creat
		if(!trie)
		{
			aux = InitNode(word[i]);

			if(!aux) return 0;

			parent->child = aux;
			trie = aux;
		}
		// daca exista, dar caracterul din nod e diferit de caracterul curent
		// ce trebuie adaugat in trie, se parcurge trie-ul pe latime, pentru a
		// determina daca exista deja vreun nod fiu cu caracterul curent
		// al cuvantului  
		else if(trie->character != word[i])
		{
			ok = 1;
			ant = NULL;

			// parcurgerea pe latime
			for(; trie != NULL; ant = trie, trie = trie->next)
			{
				// nodurile se introduc in ordine alfabetica astfel ca
				// daca se gaseste un nod al carui caracter este mai mare decat
				// caracterul ce trebuie introdus in trie, atunci caracterul
				// de introdus nu exista in trie, acesta trebuind sa fie adaugat
				if(trie->character > word[i])
				{
					ok = 0;
					break;
				}

				// daca exista nod cu acel caracter parcurgerea pe latime se opreste
				if(trie->character == word[i])
					break;
			}

			// daca nu se gaseste niciun nod pe latime cu acelasi caracter
			// cu cel care trebuie introdus
			if(ok == 0 || !trie)
			{
				// crearea nodului
				aux = InitNode(word[i]);

				if(!aux) return 0;

				// crearea legaturilor
				aux->next = trie;

				if(ant == NULL)
					parent->child = aux;
				else
					ant->next = aux;

				trie = aux;
			}
		}
	}

	// la final se marcheaza faptul ca s-a introdus acel cuvant in trie
	trie->is_word = 1;

	return 1;
}


// stergere cuvant din trie
// *to_remove este folosit pentru a determina daca word exista in trie
// daca nu exista, stergerea nu mai are loc 
void RemoveWord(ATrie ant, ATrie trie, char *word, size_t i, size_t *to_remove)
{
	// daca s-a parcurs tot trie-ul in adancime, dar mai exista caractere
	// in cuvant pentru care ar trebui sa fie apelata functia, atunci
	// cuvantul word nu exista in trie
	if(!trie && i <= strlen(word)-1)
	{
		*to_remove = 0;
		return;
	}

	// daca directia din trie pe care a intrat functia e NULL sau
	// s-a apelat functia pentru toate caracterele din cuvantul word
	if(!trie || i == strlen(word))
		return;

	// daca se afla pe radacina se apeleaza functia pentru primul fiu 
	// al acesteia
	if(trie->character == '*')
	{
		*to_remove = 1;
		ant = trie;
		trie = trie->child;
		RemoveWord(ant, trie, word, i, to_remove);
	}
	
	// daca se afla pe un nod al carui caracter e mai mic decat caracterul
	// curent din cuvantul de eliminat
	else if(trie->character < word[i])
	{
		// se cauta pe latime
		*to_remove = 1;
		while(trie && trie->character < word[i])
		{
			ant = trie;
			trie = trie->next;
		}

		// daca nu exista niciun nod cu acel caracter, atunci word nu exista
		// in trie, altfel se apeleaza functia pentru nodul curent
		if(!trie || trie->character != word[i])
		{
			*to_remove = 0;
			return;
		} 
		else 
			RemoveWord(ant, trie, word, i, to_remove);
	}
	
	// daca nodul curent contine acelasi caracter cu cel curent al cuvantului
	else if(trie->character == word[i])
	{
		*to_remove = 1;
		ant = trie;
		trie = trie->child;
		RemoveWord(ant, trie, word, ++i, to_remove);
	}

	if(!trie) return;

	// stergerea efectiva a nodului
	if(*to_remove == 1 && i < strlen(word))
	{
		// restabilirea legaturilor se face diferit in functie
		// de nodul anterior

		// daca nodul anterior se afla pe acelasi nivel cu cel
		// care trebuie eliminat                                  
		if(ant->next == trie)
		{
			// daca nodul nu mai are fii, acesta poate fi eliminat
			if(!trie->child)
			{
				ant->next = trie->next;
				free(trie);
			}
			// altfel, doar se marcheaza ca nu mai formeaza cuvant
			else
				trie->is_word = 0;
		}
		// daca nodul anterior se afla pe nivelul anterior
		else if(ant->child == trie)
		{
			// daca nodul nu mai are nici fii si nici noduri la dreapta 
			if(!trie->next && !trie->child)
			{
				ant->child = NULL;
				free(trie);
			}
			// daca are doar fiu
			else if(!trie->next && trie->child)
			{
				trie->is_word = 0;
			}
			// daca are doar nod la dreapta
			else if(trie->next && !trie->child)
			{
				ant->child = trie->next;
				free(trie);
			}
			// daca are si fiu si nod la dreapta
			else if(trie->next && trie->child)
				trie->is_word = 0;
		}
	}

	return;	
}

// cauta cuvantul word in trie
void FindWord(ATrie trie, char *word, FILE *output)
{
	size_t len = strlen(word);;
	size_t i = 0;
	size_t is_word = 0;

	// coboara de pe nivelul radacinii
	trie = trie->child;

	// parcurgere trie
	while(i < len)
	{
		// parcurgere in latime cat timp caracterul nodului curent
		// e mai mic decat caracterul curent al cuvantului
		while(trie && trie->character < word[i])
			trie = trie->next;
			
		// daca nu exista niciun nod cu acel caracter
		if(!trie || trie->character != word[i])
		{
			fprintf(output, "False\n");
			return;
		}
		// altfel, parcurgere in adancime
		else
		{
			is_word = trie->is_word;
			trie = trie->child;
		}

		++i;
	}

	// daca s-a parcurs trie-ul pentru toate caracterele din cuvant, 
	// dar nu s-a ajuns la sfarsitul unui cuvant prezent in trie
	if(!is_word)
		fprintf(output, "False\n");
	else
		fprintf(output, "True\n");

	return;
}

// afiseaza cel mai lung prefix pe care word il are in comun cu orice
// alt cuvant din trie
void FindLongestPref(ATrie trie, char *word, FILE *output)
{
	size_t len = strlen(word);
	size_t i = 0;
	size_t is_word = 0;

	trie = trie->child;

	// parcurgere trie
	while(i < len)
	{
		// parcurgere in latime
		while(trie && trie->character < word[i])
			trie = trie->next;
		
		// daca nu s-a gasit vreun nod cu acelasi caracter	
		if(!trie || trie->character != word[i])
		{
			// daca se afla la prima iteratie rezulta ca nu exista
			// niciun cuvant din trie care sa aiba in comun vreun
			// prefix cu word
			if(i == 0)
				fprintf(output, "None\n");
			else
				fprintf(output, "\n");

			return;
		}
		else
		{
			// afisare caracter
			fprintf(output, "%c", trie->character);
			// parcurgere in adancime
			trie = trie->child;
		}

		++i;
	}

	fprintf(output, "\n");
	return;
}

// afisarea tuturor cuvintelor din trie care incep cu prefixul pref
// este realizata cu 2 functii
// FindAllWithPref parcurge trie-ul cu ajutorul lui pref, iar 
// PrefRec parcurge recursiv trie-ul incepand din pozitia data de 
// FindAllWithPref si afiseaza cuvintele gasite

// in *word este pastrat cuvantul curent de pe ramura pe care se afla functia
void PrefRec(ATrie trie, char **word, size_t index, char *pref, FILE *output)
{
	// daca a intrat pe o directie nula
	if(!trie)
		return;
	
	// realocarea cuvantului si schimbarea caracterului de pe pozitia index
	++index;
	*word = realloc(*word, (index + 2) * sizeof(char));
	(*word)[index] = trie->character;
	(*word)[index+1] = '\0';

	// daca s-a gasit un cuvant, se afiseaza
	if(trie->is_word)
		// deoarece in *word se pastreaza doar caracterele parcurse recursiv,
		// trebuie folosit si pref la afisare
		fprintf(output, "%s%s ", pref, *word);

	// parcurgere in adancime
	PrefRec(trie->child, word, index, pref, output);

	// parcurgere in latime
	PrefRec(trie->next, word, --index, pref, output);
}

void FindAllWithPref(ATrie trie, char *pref, FILE *output)
{
	size_t len;
	size_t i = 0;
	size_t is_word = 0;
	char *word;

	trie = trie->child;

	if(!pref)
		len = 0;
	else
		len = strlen(pref);

	while(i < len)
	{
		while(trie && trie->character < pref[i])
			trie = trie->next;
			
		if(!trie || trie->character != pref[i])
		{
			fprintf(output, "None\n");
			return;
		}
		else
		{
			is_word = trie->is_word;
			trie = trie->child;
		}

		++i;
	}
	
	// alocare memorie pentru string-ul ce retine cuvantul
	// construit prin parcurgerea recursiva a trie-ului
	word = (char*)malloc(1 * sizeof(char));
	word[0] = '\0';

	if(is_word == 1)
		fprintf(output, "%s ", pref);

	PrefRec(trie, &word, -1, pref, output);
	fprintf(output, "\n");

	free(word);
	return;
}

// lungimea medie a cuvintelor din trie cu un anumit prefix se realizeaza similar
// cu cea de afisare a tuturor cuvintelor cu un anumit prefix, adica folosind
// o functie ce parcurge iterativ trie-ul pana la pref, si una ce parcurge recursiv

// MeanLengthRec intoarce prin efect lateral suma tuturor cuvintelor si numarul de
// cuvinte din trie

// variabila depth retine adancimea la care se afla un nod, adancimea fiind
// aceeasi cu lungimea cuvantului pana in acel nod
void MeanLengthRec(ATrie trie, size_t depth, size_t *sum, size_t *nr_words)
{
	if(!trie)
		return;
	
	MeanLengthRec(trie->child, ++depth, sum, nr_words);

	// daca ramura pana la acel nod formeaza un cuvant
	if(trie->is_word)
	{
		*sum += depth;
		++(*nr_words);
	}

	MeanLengthRec(trie->next, --depth, sum, nr_words);
}

void MeanLength(ATrie trie, char *word, FILE *output)
{
	size_t len = strlen(word);
	size_t i = 0;
	size_t is_word = 0;
	size_t depth = 0;
	size_t sum = 0;
	size_t nr_words = 0;
	float mean_length;

	trie = trie->child;

	// parcurgere iterativa
	while(i < len)
	{
		while(trie && trie->character < word[i])
			trie = trie->next;
			
		if(!trie || trie->character != word[i])
		{
			fprintf(output, "0\n");
			return;
		}
		else
		{
			++depth;
			is_word = trie->is_word;
			trie = trie->child;
		}

		++i;
	}

	// daca pref este un cuvant din trie
	if(is_word == 1)
	{
		++nr_words;
		sum += depth;
	}
		
	MeanLengthRec(trie, depth, &sum, &nr_words);

	// calcularea mediei
	if(nr_words != 0)
	{
		mean_length = (float)sum/nr_words;
		fprintf(output, "%.3f\n", mean_length);
	}
	else
		fprintf(output, "0\n");

	return;
}

// eliberarea trie-ului din memorie
void FreeTrie(ATrie trie)
{
	if(!trie)
		return;

	FreeTrie(trie->child);

	FreeTrie(trie->next);

	free(trie);
}
