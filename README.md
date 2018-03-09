Trie  
	Trie-ul este implementat folosind numai liste. Prin p = trie->child
este accesat primul fiu al lui trie, iar apoi, prin p = trie->next, sunt
accesati celalti fii ai lui trie.  
	In main este initializat trie-ul si sunt apelate functiile ce
efectueaza operatiile asupra trie-ului.   
	Functia ReadWord este folosita pentru a citi din fisierul dat ca
parametru un cuvant.  
	InitNode initializeaza un nod ce urmeaza sa fie introdus in trie.
 Functia aloca memorie pentru nod, initializeaza pointerii cu NULL si introduce
caracterul dat ca parametru in nod.  
	Functia AddWord introduce in trie cuvantul dat ca parametru. 
Aceasta parcurge iterativ trie-ul si introduce noduri noi daca este nevoie
si modifica legaturile dintre noduri.  
	Functia RemoveWord elimina din trie cuvantul dat ca parametru, daca 
acesta exista. Functia parcurge recursiv trie-ul si verifica in acelasi timp
daca acel cuvant dat ca parametru exista cu ajutorul variabilei *to_remove.
Aceasta sterge nodul curent la care se afla daca este posibil si modifica
legaturile nodului anterior, sau doar marcheaza faptul ca ramura pe care se
afla nu mai formaeza un cuvant.  
	Functia FindWord cauta iterativ in trie cuvantul dat ca parametru si
il afiseaza in cazul in care exista.  
	Functia FindLongestPref afiseaza cel mai lung prefix pe care cuvantul
dat ca parametru il are in comun cu orice alt cuvant din trie, parcurgand
iterativ trie-ul.  
	Operatiile Find_all_with_prefix si Mean_length sunt realizate utilizand
cate o functie iterativa (FindAllWithPref si MeanLength) ce parcurge trie-ul 
utilizand un prefix dat ca parametru. Apoi este apelata o functie recursiva
(PrefRec si MeanLengthRec) ce parcurge recursiv trie-ul din pozitia la care
a ramas.   
	PrefRec foloseste parametrul *word care prin care este retinut cuvantul
curent format de ramura pe care se afla functia.  
	MeanLengthRec intoarce prin efect lateral suma si numarul de cuvinte
din trie, iar media este realizata in MeanLength.  
