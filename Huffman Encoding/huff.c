#include<stdio.h>
#include<stdlib.h>
#include <math.h> 
#include<string.h>
#include "general.h"
#include "heap.h"
#include "btree.h"

void solve(FILE*);	//answer question


int main (int argc, char ** argv) {

	FILE * fp = fopen("huff.txt","r");	
	solve(fp);
	
	
	return 0;
}

void solve(FILE * fp) {

	int n;

	fscanf(fp,"%d\n",&n);


	double * A = new_double(n);

	struct heap * h1 = new_heap(n);

	struct btnode ** t4= bt_arr(2*n-1);
	
	int i = 0;

	double total = 0;

	while (fscanf(fp,"%lf\n",&A[i]) == 1) {
		insert_h(&h1,A[i],i);
		total += A[i];
		t4[i] = new_btnode(i,NULL,NULL);


		i++;
		if (i == n) {break;}
	}

	//p_heap(h1);nl();

	for (i = 0; i < n-1; i++) {
		struct node * t1 = extract_min(&h1);
		struct node * t2 = extract_min(&h1);
		double t3 = t1->value + t2->value;
		int left = t1->index;
		int right = t2->index;
		int ni = n+i;


		t4[ni] = new_btnode(ni,t4[left],t4[right]);
		insert_h(&h1,t3,ni);
		//p_heap(h1);nl();
	}
	
	
	
	pi(depth(t4[2*n-2]));nl();	
		
	return;	
}

