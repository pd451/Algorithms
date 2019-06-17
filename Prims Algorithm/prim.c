#include<stdio.h>
#include<stdlib.h>
#include <math.h> 
#include<string.h>
#include "general.h"
#include "graph.h"
#include "heap.h"

/*compute cost of minimum weight spanning tree*/

void solve(FILE*);	//answer question

static int n;		//number of vertices
static int m;		//number of edges 
static struct edge ** G;	//graph
static struct heap * h;		//heap

static int INT_MAX = 2147483647;


int main (int argc, char ** argv) {

	FILE * fp = fopen("g.txt","r");	
	solve(fp);
	
	
	return 0;
}

void solve(FILE * fp) {

	fscanf(fp,"%d\t%d\n",&n,&m);
	
	G = Graph(n);
	h = new_heap(2*n);
	int * v = new_int(n);
	int * key = new_int(n);

	int s,d,w;
		
	while ( fscanf(fp,"%d\t%d\t%d\n",&s,&d,&w) == 3) {
		insert(&G,s-1,d-1,w);
		insert(&G,d-1,s-1,w);

	}

	int i;

	insert_h(&h,0,0);

	for (i = 1; i < n; i++) {
		insert_h(&h,INT_MAX,i);
		key[i] = INT_MAX;
		v[i] = 0;
	}	
		

	while (h->size > 0) {
		struct node * t1 = extract_min(&h);

		int sc = t1->index;
	

		v[sc] = 1;

		struct edge * t2 = G[sc];
		
		while (t2 != NULL) {
			int d1 = t2->data;
			int w1 = t2->weight;

			if (w1 < key[d1] && v[d1] == 0) {
				del(&h,d1);
				insert_h(&h,w1,d1);
				key[d1] = w1;	


			}
			t2 = t2->next;
		}

	}

	long int result = 0;

	for (i = 0; i < n; i++) {
		result = result + key[i];
	}

	pi(result);nl();


	return;

}



