#ifndef __DNA_H__
#define __DNA_H__

typedef char T;

typedef struct nucleotides {
    int A, C, G, T;
} Nucleotides;

typedef struct ListNode {
    T value;
     struct ListNode* next;
     struct ListNode* prev;
}ListNode;

typedef struct List {
    size_t length; // camp in care tin numarul de elemente
    ListNode *head; // santinela 
}List;

void create(List **L) // creeza lista
{
	(*L) = (List*) malloc(sizeof(List));
	(*L)->head = NULL; // initial lista e vida
	(*L)->length = 0; // lista vida -> 0 elemente
}

void pushFront(List **L, T value) // adauga element pe prima pozitie in lista
{
	ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));

	newNode->value = value;
	newNode->prev = NULL;
	newNode->next = NULL;

	if ((*L)->length == 0) // cazul listei vide
	{
		(*L)->head = newNode;
		(*L)->head->next = (*L)->head;
		(*L)->head->prev = (*L)->head;
		(*L)->length = 1; // vom avea un singur element in lista
		return;
	}

	// in restul cazurilor
	newNode->next = (*L)->head;
	newNode->prev = (*L)->head->prev;
	(*L)->head->prev->next = newNode;
	(*L)->head->prev = newNode;
	(*L)->head = newNode;
	(*L)->length = (*L)->length + 1; // creste numarul de elemente prin adaugare
}

T front(List *L) // afiseaza primul nod din lista
{
	return L->head->value;
}

void popFront(List **L) // elimina primul nod din lista
{
	ListNode* p;

	if ((*L)->length == 0) // cazul listei vide
	{
		return;
	}

	if ((*L)->length == 1) // cazul in care e un singur element in lista
	{
		p = (*L)->head;
		free(p);
		(*L)->head = NULL; // lista vida
		(*L)->length = 0;
		return;
	}

	// in restul cazurilor
	p = (*L)->head;
	(*L)->head->prev->next = (*L)->head->next;
	(*L)->head->next->prev = (*L)->head->prev;
	(*L)->head = (*L)->head->next;
	free(p);
	(*L)->length = (*L)->length - 1; // scade numarul de elemente prin eliminare
}

void pushBack(List **L, T value) // adauga element pe ultima pozitie in lista (lista e circulara -> se adauga inainte de prima pozitie)
{
	ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));

	newNode->value = value;
	newNode->prev = NULL;
	newNode->next = NULL;

	if ((*L)->length == 0) // cazul listei vide
	{
		(*L)->head = newNode;
		(*L)->head->next = (*L)->head;
		(*L)->head->prev = (*L)->head;
		(*L)->length = 1; // vom avea un singur element in lista
		return;
	}

	// in restul cazurilor
	newNode->next = (*L)->head;
	newNode->prev = (*L)->head->prev;
	(*L)->head->prev->next = newNode;
	(*L)->head->prev = newNode;
	(*L)->length = (*L)->length + 1; // creste numarul de elemente prin adaugare
}

T back(List *L) // afiseaza ultimul nod din lista
{
	return L->head->prev->value;
}

void popBack(List **L) // elimina ultimul nod din lista
{
	ListNode* p;

	if ((*L)->length == 0) // cazul listei vide
	{
		return;
	}

	if ((*L)->length == 1) // cazul in care e un singur element in lista
	{
		p = (*L)->head;
		free(p);
		(*L)->head = NULL; // lista vida
		(*L)->length = 0;
		return;
	}

	// in restul cazurilor
	p = (*L)->head->prev;
	(*L)->head->prev->prev->next = (*L)->head;
	(*L)->head->prev = (*L)->head->prev->prev;
	free(p);
	(*L)->length = (*L)->length - 1; // scade numarul de elemente prin eliminare
}

void destroy(List **L) // distrugere lista (dezalocarea memoriei)
{
	while ((*L)->length > 0) // se elimina elementele din lista (dezalocarea memoriei)
	{
		popBack(L);
	}
	free(*L); // se dezaloca lista
	(*L)->head = NULL; // lista vida
	L = NULL; // lista nu mai pointeaza catre niciun reziduu
}

List* strToList(char* s) // adaptor de la sir de caractere la lista
{
	List *L;
	int i = 0;

	create(&L);
	while(s[i] != '\0')
	{
		pushBack(&L, s[i]);
		i = i + 1;
	}

	return L;
}

char* listToStr(List** L) // adaptor de la lista la sir de caractere
{
	char *s = (char*) malloc(((*L)->length + 1) * sizeof(char));
	int i = 0;

	while((*L)->length > 0)
	{
		s[i] = (*L)->head->value;
		popFront(L);
		i = i + 1;
	}

	s[i] = '\0'; // siguranta incheierii sirului

	return s;
}

Nucleotides *countNucleotides(char *s)
{
	List *DNA;
	Nucleotides* n = (Nucleotides*) malloc(sizeof(Nucleotides));
	// initializarea valorilor structurii
	n->T = 0;
	n->C = 0;
	n->G = 0;
	n->A = 0;

	DNA = strToList(s);
	while(DNA->length > 0)
	{
		if (front(DNA) == 'T')
		{
			n->T = n->T + 1;
		}
		if (front(DNA) == 'C')
		{
			n->C = n->C + 1;
		}
		if (front(DNA) == 'G')
		{
			n->G = n->G + 1;
		}
		if (front(DNA) == 'A')
		{
			n->A = n->A + 1;
		}

		popFront(&DNA);
	}

	destroy(&DNA);

	return n;
}

char *computeRNA(char *s)
{
	List *DNA, *RNA;
	char *rna;

	DNA = strToList(s);
	create(&RNA);

	while(DNA->length > 0)
	{
		if (front(DNA) == 'T')
		{
			pushBack(&RNA, 'U');
		}
		else
		{
			pushBack(&RNA, DNA->head->value);
		}

		popFront(&DNA);
	}

	rna = listToStr(&RNA);

	destroy(&DNA);
	destroy(&RNA);

	return rna;
}

char *complementDNA(char *s)
{
	List *DNA, *cDNA;
	char *cdna;
	DNA = strToList(s);
	create(&cDNA);

	while(DNA->length > 0)
	{
		if (back(DNA) == 'T')
		{
			pushBack(&cDNA, 'A');
		}
		else if (back(DNA) == 'A')
		{
			pushBack(&cDNA, 'T');
		}
		else if (back(DNA) == 'G')
		{
			pushBack(&cDNA, 'C');
		}
		else
		{
			pushBack(&cDNA, 'G');
		}

		popBack(&DNA);
	}

	cdna = listToStr(&cDNA);

	destroy(&DNA);
	destroy(&cDNA);

	return cdna;
}

int countMutations(char *s1, char *s2)
{
	List *DNA1, *DNA2;
	int dif = 0;

	DNA1 = strToList(s1);
	DNA2 = strToList(s2);

	while(DNA1->length > 0 && DNA2->length > 0)
	{
		if (front(DNA1) != front(DNA2))
		{
			dif = dif + 1;
		}
		popFront(&DNA1);
		popFront(&DNA2);
	}

	destroy(&DNA1);
	destroy(&DNA2);

	return dif;

}

int levenshteinDistance(char *s1, char* s2)
{
	List *DNA1, *DNA2;
	int levDist = 0;

	DNA1 = strToList(s1);
	DNA2 = strToList(s2);

	while(DNA1->length > 0 && DNA2->length > 0)
	{
		if (front(DNA1) != front(DNA2))
		{
			levDist = levDist + 1;
		}
		popFront(&DNA1);
		popFront(&DNA2);
	}

	levDist = levDist + abs(DNA1->length - DNA2->length);

	destroy(&DNA1);
	destroy(&DNA2);

	return levDist;
}
#endif
