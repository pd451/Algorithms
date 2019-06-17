#include<stdio.h>
#include<stdlib.h>
#include <math.h> 
#include<string.h>

/*Implementation of Binary Tree*/

struct btnode {
	int data;
	struct btnode * left;
	struct btnode * right;
};

struct btnode * new_btnode(int,struct btnode *,struct btnode *);	//new binary tree node
void p_tree(struct btnode*);	//print tree in order
struct btnode ** bt_arr(int);	//new array of binary tree nodes
int height(struct btnode *);	//height of subtree with argument as its root
int depth(struct btnode *);	//depth of a subtree with argument as its root

int depth (struct btnode * r) {
	if (r == NULL) {return -1;}

	if (r->left == NULL && r->right == NULL) {return 0;}

	if (1 + depth(r->left) < 1 + depth(r->right)) {
		return 1 + depth(r->left);
	}
	else {
		return 1 + depth(r->right);
	}
}

int height (struct btnode * r) {
	if (r == NULL) {return -1;}
	if (1 + height(r->right) > 1 + height(r->left)) {
		return 1 + height(r->right);
	}
	else {
		return 1 + height(r->left);
	}
}

struct btnode ** bt_arr(int n) {
	return (struct btnode **) malloc(n*sizeof(struct btnode*));
}

void p_tree(struct btnode * root) {
	if (root == NULL) {return;}
	else { printf("%d\n",root->data);}

	p_tree(root->left);
	p_tree(root->right);
	return;
}

struct btnode * new_btnode (int data,struct btnode * l, struct btnode * r) {

	struct btnode * r1 = (struct btnode *) malloc(sizeof (struct btnode));
	r1->data = data;
	r1->left = l;
	r1->right = r;
	return r1;
}
