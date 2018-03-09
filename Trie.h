#ifndef _TRIE_
#define _TRIE_

	typedef struct Trie {
		char character;
		unsigned char is_word;
		struct Trie *child;
		struct Trie *next;
	} TTrie, *ATrie;
	
#endif