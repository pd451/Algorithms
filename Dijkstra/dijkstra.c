#include<stdio.h>
#include<stdlib.h>
#include <math.h> 
#include<string.h>

struct edge {
	int data;
	int weight;
	struct edge * next;
};

struct node {
	int value;
	int index;
};

struct heap {
	struct node ** items;
	int size;
	int cap;
};

/*Runs Dijsktra's Algorithm in o(nlogn) with binary min heap, output shortest path distance from source to select indices*/

int power(int,int);	//a^b

void pi(int);		//print int
void pf(float);		//print float
void pd(double);	//print double
void ps(char*);		//print string
void tb();		//print tab
void nl();		//print newline
void pfm(float**,int,int);	//print float matrix
void pim(int**,int,int);	//print int matrix
void pdm(double**,int,int);	//print double matrix
void p_error(char*);			//prints error

int ** new_int_mat(int,int);		//declare int matrix of r x c
float ** new_float_mat(int,int);	//declare float matrix of r x c
double ** new_double_mat(int,int);	//declare double matrix of r x c


int * new_int_inf(int);			//int array with inf
int * new_int(int);			//int array
float * new_float(int);			//float array
double * new_double(int);		//double array

void pia(int*,int);			//print int array
void pfa(float*,int);			//print float array
void pda(double*,int);			//print double array

struct edge ** Graph(int);		//Graph of int vertices
void insert(struct edge ***,int,int,int);	//insert with weights (source, destination, weight)

void swap(int*,int*);			//swap integer values
struct heap * new_heap(int);		//heap of size int
void insert_h(struct heap **,int,int);	//insert into heap (value, index)
struct node * new_node(int,int);	//new node	(value, index) === (distance, vertex number)
void p_heap(struct heap *);		//prints (distance,index) pairs in heap
struct node * extract_min(struct heap **);		//remove min element from heap
void heapify(struct heap **, int);	//restores heap property
void delete(struct heap **,int);	//delete heap (index)

int parent(int);			//returns relevant indices
int right(int);
int left(int);

void input_graph(FILE*);		//input graph from file
void p_graph(struct edge**,int);	//print graph

void DA();				//dijistkra algorithm
void solve();				//solve question asked

static int * distance;			//distance from source
static int * spt;			//checks if vertex was examined
static struct edge ** G;		//graph
struct heap * hp;			//heap
static int n12;
static int INT_MAX = 2147483647;



int main (int argc, char ** argv) {
	
	FILE* fp = fopen("data.txt","r");
	input_graph(fp);
	DA();
	solve();
	
	
	
	return 0;
}

void delete(struct heap ** h_ref, int index) {
	struct heap * t1 = *h_ref;
	struct node ** t2 = t1->items;
	int len = t1->size;
	int i;
	int j = -1;
	for (i = 0; i < len; i++) {
		if (t2[i]->index == index) {j = i;break;}
	}
	
	if (j == -1) {return;}

	t2[j]->value = -10;
	
	while (j != 0) {
		struct node * t3 = t2[parent(j)];
		t2[parent(j)] = t2[j];
		t2[j] = t3;
		j = parent(j);
	}
	extract_min(h_ref);

	return;
	
}

void solve() {
	int t1[10] = {7,37,59,82,99,115,133,165,188,197};

	int i;
	
	for (i = 0; i < 10; i++) {
		pi(distance[t1[i]-1]);

		if (i != 9) {ps(",");}
	}

	nl();


}

void DA() {

	int s = 0;
	distance[s] = 0;

	
	int * spt = new_int(n12);
	
	insert_h(&hp,distance[s],s);

	while (hp->size != 0) {
		struct node *t1 = extract_min(&hp);
		int i = t1->index;
		

		if (spt[i] == 0) {
			spt[i] = 1;

			struct edge * t2 = G[i];

			while (t2 != NULL) {
				int d = t2->data;
				int w = t2->weight;
			
				if (spt[d] == 0 && distance[i] != INT_MAX && distance[d] > distance[i] + w) {
					distance[d] = distance[i] + w;
					insert_h(&hp,distance[d],d);

				}
				t2 = t2->next;
			}

		}
		

	}

	
	return;	
}



void input_graph(FILE * fp) {
	
	int a,b,c;		//(a,b,c) === (index,destination,weight)
	int i;
	fscanf(fp,"%d",&a);

	n12 = 200;


	hp = new_heap(power(n12,3));
	distance = new_int_inf(n12);
	spt = new_int(n12);
	G = Graph(n12);

	for (i = 0; i < n12; i++) {
		while(fscanf(fp,"%d,%d",&b,&c) == 2) {
			insert(&G,i,b-1,c);
			insert(&G,b-1,i,c);
		}
		
	
	}

	

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

void swap (int * x, int * y) {
	int temp = *x;
	*x = *y;
	*y = temp;
	return;
}

struct edge ** Graph(int n) {
	struct edge ** t1 = (struct edge **) malloc(n * sizeof(struct edge*));	
	return t1;
}

struct edge * new_edge(int d, int w) {
	struct edge * t1 = (struct edge*) malloc(sizeof(struct edge));
	t1->data = d;
	t1->weight = w;
	return t1;
}

void insert(struct edge *** g_ref, int s, int d, int w) {
	struct edge ** G = *g_ref;
	if (G[s] == NULL) {
		struct edge * t1 = new_edge(d,w);
		G[s] = t1;
	}
	else {
		struct edge * t1 = G[s];

		if (t1->data == d) {return;}
		
		while (t1->next != NULL) {

			if (t1->data == d) {return;}

			t1 = t1->next;
		}

		struct edge * t2 = new_edge(d,w);
		t1->next = t2;
	}
	return;
}

int * new_int_inf(int n) {
	int * result = new_int(n);
	int i;
	int t1 = 2147483647;
	for (i = 0; i < n; i++) {
		result[i] = t1;
	}
	return result;
}

int power(int a, int b) {
	int result = 1;
	int i;
	for (i = 0; i < b; i++) {
		result = result * a;
	}
	return result;
}


void pia(int* a, int b) {
	int i;
	for (i = 0; i < b; i++) {
		pi(a[i]);tb();
	}	
	nl();
}

void pfa(float* a, int b) {
	int i;
	for (i = 0; i < b; i++) {
		pf(a[i]);tb();
	}	
	nl();
}

void pda(double* a, int b) {
	int i;
	for (i = 0; i < b; i++) {
		pd(a[i]);tb();
	}	
	nl();
}

void p_error(char* a) {
	printf("Error has occurred:"); tb(); printf("%s",a); nl();
}

int * new_int(int n) {
	int * a = (int*) malloc(n*sizeof(int));
	return a;
}

float * new_float(int n) {
	float * a = (float*) malloc(n*sizeof(float));
	return a;
}

double * new_double(int n) {
	double * a = (double*) malloc(n*sizeof(double));
	return a;
}	

double ** new_double_mat(int r, int c) {
	int i;
	
	if (r < 1 || c < 1) {p_error("new_double_mat"); return NULL;}	

	double ** A = (double**) malloc(r*sizeof(double*));
	for (i = 0; i < r; i++) {
		A[i] = (double*) malloc(c*sizeof(double));
	}
	return A;
}

void pfm(float ** A, int r, int c) {
	int i,j;
	
	if (r < 1 || c < 1) {p_error("pfm"); return;}	

	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			pf(A[i][j]);tb();
		}
		nl();
	}

	return;
}

void pdm(double ** A, int r, int c) {
	int i,j;
	
	if (r < 1 || c < 1) {p_error("pdm"); return;}	

	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			pd(A[i][j]);tb();
		}
		nl();
	}

	return;
}

void pim(int ** A, int r, int c) {
	int i,j;
	
	if (r < 1 || c < 1) {p_error("pim"); return;}	

	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			pi(A[i][j]);tb();
		}
		nl();
	}

	return;
}

void pi (int a) {
	printf("%d",a);
}

void pf (float a) {
	printf("%f",a);
}

void pd (double a) {
	printf("%f",a);
}

void ps (char* a) {
	printf("%s",a);
}

int ** new_int_mat(int r, int c) {
	int i;
	
	if (r < 1 || c < 1) {pi(r); tb(); pi(c); p_error("new_int_mat"); return NULL;}	

	int ** A = (int**) malloc(r*sizeof(int*));
	for (i = 0; i < r; i++) {
		A[i] = (int*) malloc(c*sizeof(int));
	}
	return A;
}

float ** new_float_mat(int r, int c) {
	int i;
	
	if (r < 1 || c < 1) {p_error("new_float_mat"); return NULL;}	

	float ** A = (float**) malloc(r*sizeof(float*));
	for (i = 0; i < r; i++) {
		A[i] = (float*) malloc(c*sizeof(float));
	}
	return A;
}



void tb() {
	printf("\t");
}

void nl() {
	printf("\n");
}

void p_graph(struct edge** G, int len) {
	int i;
	
	for (i = 0; i < len; i++) {
		pi(i);ps(":");tb();

		struct edge * t1 = G[i];

		while (t1 != NULL) {
			pi(t1->data); ps(","); pi(t1->weight); tb();
			t1 = t1->next;
		}
		nl();
	}
}
