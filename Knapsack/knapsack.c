#include<stdio.h>
#include<stdlib.h>
#include <math.h> 
#include<string.h>
#include "general.h"

void solve(FILE*);	//answer question


int main (int argc, char ** argv) {

	FILE * fp = fopen("k11.txt","r");	
	solve(fp);
	
	
	return 0;
}

void solve(FILE * fp) {

	int W;

	int n;

	fscanf(fp,"%d\t%d\n",&W,&n);

	pi(W);nl();
	pi(n);nl();

	int ** A = new_int_mat(n+1,W+1);

	int * weights = new_int(n);
	int * values = new_int(n);

	int i = 0;

	while ( fscanf(fp,"%d\t%d\n",&values[i],&weights[i]) == 2) {
		
		i++;
		if (i == n) {break;}
	}	

	int x;

	for (i = 1; i < n+1; i++) {
		for (x = 0; x < W+1; x++) {
			int t2 = A[i-1][x];
			

			if (weights[i-1] > x) {
				A[i][x] = t2;
				continue;
			}

			int t3 = A[i-1][x-weights[i-1]] + values[i-1];

			if (t2 > t3) {
				A[i][x] = t2;
			}
			else {
				A[i][x] = t3;
			}
		}

		pi(i);nl();
	}

	pi(A[n][W]); nl();
		
	return;	
}

