#include<stdio.h>
#include<stdlib.h>
//replace each node with sum of its predecessor and successor
#define MAX_Q_SIZE 100
struct node{
	int data;
	struct node* left;
	struct node* right;
	struct node* parent;
};
int arr[100];
int top=0;
int pot =1;
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

void push (int data){
	if (top == 0)
		arr[top++] = 0;
    arr[top++] = data;
}

int pop_beg(){
    int temp;
    temp = (arr[pot-1] + arr[pot+1]);
	pot++;
    return temp;
}
void inorder_traversal_store(struct node* root){
	if(root == NULL)
		return;
	inorder_traversal_store(root->left);
	printf("%d ", root->data);
	push(root->data);
	inorder_traversal_store(root->right);
}

void inorder_traversal_sum(struct node* root){
	if(root == NULL)
		return;
	inorder_traversal_sum(root->left);
	printf("%d ", root->data);
    root->data = pop_beg();
	inorder_traversal_sum(root->right);
}
void inorder_traversal(struct node* root){
	if(root == NULL)
		return;
	inorder_traversal(root->left);
	printf("%d ", root->data);
	inorder_traversal(root->right);
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
	inorder_traversal_store(root);
	inorder_traversal_sum(root);
	inorder_traversal(root);
	n= root->left->right->right;
	
	return 0;
}
