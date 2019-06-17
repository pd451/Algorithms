#include<stdio.h>
#include<stdlib.h>
#include <math.h> 
#include<string.h>

struct edge {
	int data;
	struct edge * next;
};

/*Given a list of constraints, verifies if problem has a satisfying assignment*/

int power(int,int);	//compute a^b
void pi(int);		//print int
void pf(float);		//print float
void pd(double);	//print double
void ps(char*);		//print string
void tb();		//print tab
void nl();		//print newline
void pfm(float**,int,int);	//print float matrix
void pim(int**,int,int);	//print int matrix
void pdm(double**,int,int);	//print double matrix
int ** new_int_mat(int,int);		//declare int matrix of r x c
float ** new_float_mat(int,int);	//declare float matrix of r x c
double ** new_double_mat(int,int);	//declare double matrix of r x c
void p_error(char*);			//prints error
struct edge ** Graph(int);		//Graph of int vertices
void insert(struct edge ***,int,int); 	//inserts directed edge between int1 int2
struct edge * new_edge(int);		//creates an edge with data int
void print_graph(struct edge**,int);	//print graph of size int
void input_graph(FILE *);		//input graph from file pointer
void DFS1(int);				//perform DFS on graph, for 1st pass
void DFS11();				//DFS loop 1st iter
void DFS2(int,int);			//perform DFS on graph, for 2nd pass
void DFS22();				//DFS loop 2nd iter
int * new_int(int);			//int array
void pia(int*,int);			//print int array
void verify();				//verifies if problem is 2sat

static int n1;				//length
static int time = 0;
static struct edge ** G;		//original graph
static struct edge ** R;		//reverse graph
static int * v1;			//1st visited array
static int * order;			//rank first to last in 1st pass
static int * v2;			//2nd visited array
static int * source;			//source vertex wher explored

int main (int argc, char ** argv) {
	FILE * fp = fopen("2sat6.txt","r");	
	input_graph(fp);
	fclose(fp);
	DFS11();
	DFS22();

	verify();
	
	return 0;
}

void verify() {
	int i;
	int t1 = n1 / 2;
	int f1 = 0;
	
	for (i = 0; i < t1; i++) {
		int index = 2*i;

		if (source[index] == source[index+1]) {
			f1 = 1;
			break;
		}

	}

	pi(t1);nl();

	if (f1 == 0) {
		ps("2SAT");
		nl();
	}
	else {
		ps("NOT 2SAT");
		nl();
	}

	return;
}

void pia(int* a, int b) {
	int i;
	for (i = 0; i < b; i++) {
		pi(a[i]);tb();
	}	
	nl();
}

void DFS22() {
	int i;
	for (i = n1-1; i >= 0; i--) {
		if (v2[order[i]] == 0) {
			DFS2(order[i],order[i]);
		}
	}

	return;
}

void DFS2(int s, int c1) {
	if (v2[c1] == 1) {return;}

	v2[c1] = 1;
	source[c1] = s;

	struct edge * t1 = G[c1];

	while (t1 != NULL) {

		int t2 = t1->data;

		if (v2[t2] == 0) {
			DFS2(s,t2);
		}
		
		t1 = t1->next;
	}
	
	return;
}

void DFS11() {
	int i;
	for (i = n1-1; i >= 0; i--) {
		if (v1[i] == 0) {
			DFS1(i);
		}
	}

	return;
}

void DFS1(int s) {

	if (v1[s] == 1) {return;}

	v1[s] = 1;
	struct edge * t1 = R[s];

	while (t1 != NULL) {

		int t2 = t1->data;

		if (v1[t2] == 0) {
			DFS1(t2);
		}
		
		t1 = t1->next;
	}

	order[time] = s;
	time++;
	
	return;
}

void input_graph(FILE * fp) {
	int a,b;
	fscanf(fp,"%d\n",&n1);
	n1 = 2 * n1;


	v1 = new_int(n1);
	order = new_int(n1);
	v2 = new_int(n1);
	source = new_int(n1);

	G = Graph(n1);
	R = Graph(n1);

	while (fscanf(fp,"%d %d\n",&a,&b) != -1) {
		int a1,a2,b1,b2;

		if (a > 0) {
			int t1 = 2*(a-1);
			a2 = t1;
			a1 = t1+1;
		}

		else {
			int t1 = 2*(-1*a-1);
			a1 = t1;
			a2 = t1+1;
		}

		if (b > 0) {
			int t1 = 2*(b-1);
			b2 = t1;
			b1 = t1+1;
		}

		else {
			int t1 = 2*(-1*b-1);
			b1 = t1;
			b2 = t1+1;
		}

		insert(&G,a1,b2);
		insert(&G,b1,a2);

		insert(&R,b2,a1);
		insert(&R,a2,b1);
	
	}


	return;
}

void print_graph(struct edge ** G, int n) {
	if (G == NULL) {return;}
	int i;
	for (i = 0; i < n; i++) {
		pi(i);ps(":");tb();
		struct edge * ptr = G[i];
		while (ptr != NULL) {
			pi(ptr->data);tb();
			ptr = ptr->next;
		}
		nl();
	}
	return;
}

struct edge * new_edge(int n) {
	struct edge * t1 = (struct edge*) malloc(sizeof(struct edge));
	t1->data = n;
	return t1;
}

void insert(struct edge *** g_ref, int s, int d) {
	struct edge ** G = *g_ref;
	if (G[s] == NULL) {
		struct edge * t1 = new_edge(d);
		G[s] = t1;
	}
	else {
		struct edge * t1 = G[s];

		if (t1->data == d) {return;}
		
		while (t1->next != NULL) {

			if (t1->data == d) {return;}

			t1 = t1->next;
		}

		struct edge * t2 = new_edge(d);
		t1->next = t2;
	}
	return;
}

struct edge ** Graph(int n) {
	struct edge ** t1 = (struct edge **) malloc(n * sizeof(struct edge*));	
	return t1;
}

void p_error(char* a) {
	printf("Error has occurred:"); tb(); printf("%s",a); nl();
}

int * new_int(int n) {
	int * a = (int*) malloc(n*sizeof(int));
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
