#include<stdio.h>
#include<stdlib.h>
#include <math.h> 
#include<string.h>

/*Implmentation of a binary min heap*/

struct node {
	int value;	//key that is used to sort array
	int index;	//supplemental data
};

struct heap {
	struct node ** items;
	int size;
	int cap;
};

struct heap * new_heap(int);		//heap of size int
void insert_h(struct heap **,int,int);	//insert into heap (value, index)
struct node * new_node(int,int);	//new node	(value, index) === (distance, vertex number)
void p_heap(struct heap *);		//prints (distance,index) pairs in heap
struct node * extract_min(struct heap **);		//remove min element from heap
void heapify(struct heap **, int);	//restores heap property
void del(struct heap **,int);		//delete heap (index)
int peek(struct heap *); 		//returns (value) at index 0 of heap
void decrease_key(struct heap **,int,int);	//decrease key of (heap, key, new value)
int search_h (struct heap *,int);		//(heap, index) -> performs linear search and returns index

int parent(int);			//returns relevant indices
int right(int);
int left(int);

static int INT_MIN = -2147483647;

int peek(struct heap * a) {
	if (a->size <= 0) {printf("No elements\n");return -1;}

	return a->items[0]->value;
}

int search_h (struct heap * t1, int index) {
	struct node ** t2 = t1->items;
	int n = t1->size;
	int i;
	for (i = 0; i < n; i++) {
		if (t2[i]->index == index) {
			return i;
		}
	}
	
	return -1;
}

void decrease_key(struct heap ** h, int index, int new_val) {
	struct heap * t1 = *h;
	int t2 = search_h(t1,index);
	if (t2 == -1) {return;}

	struct node ** t3 = t1->items;
	
	while ( t2 != 0 && t3[parent(t2)]->value > t3[t2]->value ) {
		struct node * t4 = t3[parent(t2)];
		t3[parent(t2)] = t3[t2];
		t3[t2] = t4;
		t2 = parent(t2);
	}
	

	return;
}


void del(struct heap ** h_ref, int index) {
	struct heap * t1 = *h_ref;
	struct node ** t2 = t1->items;
	int len = t1->size;
	int i;
	int j = -1;
	for (i = 0; i < len; i++) {
		if (t2[i]->index == index) {j = i;break;}
	}
	
	if (j == -1) {return;}

	t2[j]->value = INT_MIN;
	
	while (j != 0) {
		struct node * t3 = t2[parent(j)];
		t2[parent(j)] = t2[j];
		t2[j] = t3;
		j = parent(j);
	}
	extract_min(h_ref);

	return;
	
}

struct node * extract_min (struct heap ** h) {

	struct heap * h1 = *h;

	if (h1->size <= 0) {
	        return NULL;
	}
 
    	if (h1->size == 1) {
        	h1->size--; 
        	return h1->items[0]; 
    	} 
  
    
    struct node * t1 = h1->items[0]; 
    h1->items[0] = h1->items[h1->size-1]; 
    h1->size--; 
    heapify(h,0); 
  
    return t1; 
}

void heapify(struct heap ** h, int i) {

	struct heap * h1 = *h;
    	int l = left(i); 
    	int r = right(i); 
    	int smallest = i; 

    	if (l < h1->size && h1->items[l]->value < h1->items[i]->value) {
        	smallest = l; 
	}

    	if (r < h1->size && h1->items[r]->value < h1->items[smallest]->value) {
        	smallest = r; 
	}

    	if (smallest != i) { 
        	struct node * t1 = h1->items[i];
		h1->items[i] = h1->items[smallest];
		h1->items[smallest] = t1;
        	heapify(h,smallest);
    	} 
}  

void p_heap(struct heap * t1) {
	int t2 = t1->size;
	struct node ** t3 = t1->items;
	int i;
	for (i = 0; i < t2; i++) {
		struct node * t4 = t3[i];

		if (t4 != NULL) {
			pi(t4->value);ps(",");pi(t4->index);tb();
		}

		else {
			ps("NULL,NULL");tb();
		}
	}

	nl();
	
	return;

}


struct node * new_node(int val, int ind) {
	struct node * a = (struct node *) malloc(sizeof(struct node));
	a->index = ind;
	a->value = val;
	return a;
}

int parent(int i) { return (i-1)/2; } 
      
int left(int i) { return (2*i + 1); } 
  
int right(int i) { return (2*i + 2); } 

void insert_h(struct heap ** a_r, int val, int ind) {

	struct heap * t1 = *a_r;
	
	if (t1->size == t1->cap) {ps("Cap Exceeded");nl();return;}

	struct node ** t2 = t1->items;
	t2[t1->size] = new_node(val,ind);
	int i = t1->size;
	t1->size++;
	
	while (i != 0 && t2[parent(i)]->value > t2[i]->value) {
    		
		struct node * t3 = t2[parent(i)];
		t2[parent(i)] = t2[i];
		t2[i] = t3; 
       		
       		i = parent(i); 
    	} 
	
	return;
}

struct heap * new_heap(int n) {
	struct heap * a = (struct heap*) malloc(sizeof(struct heap));
	a->cap = n;
	a->items = (struct node **) malloc(n*sizeof(struct node));
	a->size = 0;
	return a;
}
