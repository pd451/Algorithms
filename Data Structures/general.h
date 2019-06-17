/*This is a general functions library, check function declarations for more information*/

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
void pfa(float*,int);		//print float array
void pia(int*,int);		//print int array
void pda(double*,int);		//print double array

int ** new_int_mat(int,int);		//declare int matrix of r x c
float ** new_float_mat(int,int);	//declare float matrix of r x c
double ** new_double_mat(int,int);	//declare double matrix of r x c


int * new_int_inf(int);			//int array with inf
long int * new_long_int(int);		//int array
int * new_int(int);			//int array
float * new_float(int);			//float array
double * new_double(int);		//double array

void merge_sort(long int**,int,int);	//(A,0,A.length-1);
void merge(long int**,int,int,int);	//(A,l,m,r)

int search(int*,int,int,int); 	//(A,left,right,key)


int search(int* a, int l,int r, int k) {
	if (l > r) {return -1;}

	int mid = (l+r) / 2;

	if (a[mid] == k) {return mid;}

	if (a[mid] > k) {return search(a,l,mid-1,k);}

	return search(a,mid+1,r,k);
	
}

void merge_sort(long int**a, int l, int r) {
	if (l < r) {
		int m = (l+r)/2;
		merge_sort(a,l,m);
		merge_sort(a,m+1,r);
		merge(a,l,m,r);
	}
}

void merge (long int **a, int l, int m, int r) {
	int n1 = m-l+1;
	int n2 = r-m;

	long int * L = new_long_int(n1);
	long int * R = new_long_int(n2);
	long int * A = *a;
	
	int i;

	for (i = l; i <= m; i++) {
		L[i-l] = A[i];
	}

	for (i = m+1; i <= r; i++) {
		R[i-m-1] = A[i];
	}

	int lc = 0;
	int rc = 0;
	int ac = 0;

	while (lc < n1 && rc < n2) {

		if (L[lc] < R[rc]) {
			A[l+ac] = L[lc];
			lc++;
		}

		else {
			A[l+ac] = R[rc];
			rc++;
		}
		
		ac++;
	}

	while (lc < n1) {
		A[l+ac] = L[lc];
		lc++;
		ac++;
	}

	while (rc < n2) {
		A[l+ac] = R[rc];
		rc++;
		ac++;
	}
	
	free(L);
	free(R);
	return;
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

long int * new_long_int(int n) {
	long int * a = (long int*) malloc(n*sizeof(long int));
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

int * new_int_inf(int n) {
	int * result = new_int(n);
	int i;
	int t1 = 2147483647;
	for (i = 0; i < n; i++) {
		result[i] = t1;
	}
	return result;
}
