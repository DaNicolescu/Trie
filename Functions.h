/* NICOLESCU Daniel-Marian - 314CB */
#ifndef _FUNCTIONS_
#define _FUNCTIONS_

	size_t ReadWord(char**, FILE*);
	ATrie InitNode(char);
	void GetIndex(char, size_t*);
	size_t AddWord(ATrie, char*);
	void RemoveWord(ATrie, ATrie, char*, size_t, size_t*);
	void FindWord(ATrie, char*, FILE*);
	void FindLongestPref(ATrie, char*, FILE*);
	void PrefRec(ATrie, FILE*);
	void FindAllWithPref(ATrie, char*, FILE*);
	void MeanLength(ATrie, char*, FILE*);
	void FreeTrie(ATrie);

#endif