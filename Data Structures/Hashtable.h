#include<stdio.h>
#include<stdlib.h>
#include <math.h> 
#include<string.h>

struct Node {
	int data;
	int index;
	struct Node * next;
};

/*Implementation of Hash Table as Array of Node*/

void insert(struct Node***,int,int,int);	//(Table Reference, data, index, length)
int lookup(struct Node**,int,int,int);		//(Table, data, index, length)	1-> true, 0 -> false
int hash(int,int);			//(data, length)
struct Node ** new_table(int);		//(length) new hash table
void p_table(struct Node**,int);	//print (table,length)
void clear(struct Node***,int);		//remove

void clear(struct Node *** a, int n) {
	struct Node ** t = *a;
	int i;
	for (i = 0; i < n; i++) {
		struct Node * t1 = t[i];
		struct Node * t2 = t1;
		while(t1 != NULL) {
			t2 = t1->next;
			free(t1);
			t1 = t2;
		}
		t[i] = NULL;
	}
}

void p_table(struct Node ** t, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d:\t",i);

		struct Node * t2 = t[i];
		while (t2 != NULL) {
			printf("%d\t",t2->data);
			t2 = t2->next;
		}
		printf("\n");
	}

	return;
}

struct Node ** new_table(int n) {
	struct Node ** t1 = (struct Node**) malloc(n*sizeof(struct Node*));
	return t1;
}

void insert (struct Node ***ref, int data, int ind, int n) {
	struct Node ** HT = *ref;
	int index = hash(data,n);

	if (HT[index] == NULL) {
		struct Node * t1 = (struct Node *) malloc(sizeof(struct Node));
		t1->data = data;
		t1->index = ind;
		HT[index] = t1;
		return;
	}
	
	struct Node * t1 = HT[index];

	

	while (t1->next != NULL) {
		
		t1 = t1->next;
	}

	struct Node * t2 = (struct Node *) malloc(sizeof(struct Node));
	t2->data = data;
	t2->index = ind;
	t1->next = t2;
	return;

}

int lookup (struct Node** t, int data, int ind, int n) {
	int index = hash(data,n);
	
	if (t[index] == NULL) {return -1;}
	
	struct Node * t1 = t[index];

	while (t1 != NULL) {

		if (t1->data == data && t1->index == ind) {return t1->index;}

		t1 = t1->next;

	}	

	return 0;
}

int hash (int data, int n) {
	int tp;
	if (data < 0) {tp = -1 * data;}
	else {tp = data;} 
	return tp % n;
}
