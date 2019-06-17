/*This file contains an implementation of a graph in the form of an adjacency list*/

struct edge {
	int data;	//index of neighbor
	int weight;	//weight of edge between neighbor and source
	struct edge * next;
};

struct edge ** Graph(int);			//Graph of int vertices
void insert(struct edge ***,int,int,int);	//insert with weights (source, destination, weight)
struct edge * new_edge(int, int);		//edge (destination, weight)
void p_graph(struct edge**, int);		//print graph


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
