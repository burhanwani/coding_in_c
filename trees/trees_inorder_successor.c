#include<stdio.h>
#include<stdlib.h>
//finding the inorder successor in a binary search tree
#define MAX_Q_SIZE 100
struct node{
	int data;
	struct node* left;
	struct node* right;
	struct node* parent;
};

struct node* newnode(int data){
	struct node* new = (struct node*)malloc(sizeof(struct node*));
	new->data = data;
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	return new;
}
int min_val(struct node* p){
	while(p->left != NULL){
		p=p->left;
	}
	return (p->data);
}

int inorder_succ(struct node* n, struct node* root){
	struct node* p;
	if(n->right != NULL){
		return min_val(n->right);
	}else {
		p = n->parent;
		while(p!=NULL && n== p->right){
			n = p ;
			p = p->parent;
		}
		return p->data;
	}
}
struct node* insert_bst (struct node * n, int data){
	struct node* temp;
	if (n == NULL){
		return (newnode(data));// returns the new root the first time
	}else if ( data < n->data){
		temp = insert_bst(n->left, data);
		n->left = temp;
		temp->parent = n;
	} else {
		temp = insert_bst(n->right, data);
		n->right = temp;
		temp->parent = n;
	}
	return n; //return unchanged node pointer

}

int main(){
	struct node* root = NULL;
	struct node* n;
	int temp;
	root = insert_bst( root, 5);
	root = insert_bst(root, 2);
	root = insert_bst(root, 3);
	root = insert_bst(root, 10);
	root = insert_bst(root, 20);
	root = insert_bst(root, 1);
	root = insert_bst(root, 4);
	n = root->left->right->right;
	temp = inorder_succ(n , root);
	printf("inorder succ is %d ", temp);
	
	return 0;
}
