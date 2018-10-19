#include<stdio.h>
#include<stdlib.h>
//level order traversal of tree using recursion and queue
#define MAX_Q_SIZE 100
struct node{
	int data;
	struct node* left;
	struct node* right;
};

int height (struct node* root){
	int lheight, rheight;
	if (root == NULL){
		return -1;
	}
	lheight = height(root->left);
	rheight = height(root->right);
	if (lheight > rheight)
		return (lheight + 1);
	else 
		return (rheight +1);
}
void print_givenlevel(struct node* root, int level){
	if(root == NULL){
		return;
	}
	if(level == 0)
		printf("%d ",root->data);
	else {
		print_givenlevel(root->left, level-1);
		print_givenlevel(root->right, level -1);

	}
}

void print_levelorder(struct node* root, int height){
	int i;
	for (i=0;i<=height;i++){
		print_givenlevel(root, i);
	}
}

struct node* newnode(int data){
	struct node* new = (struct node*)malloc(sizeof(struct node*));
	new->data = data;
	new->left = NULL;
	new->right = NULL;
	return new;
}

void enqueue(struct node* node, int * rear, struct node** queue){
	queue[++(*rear)]= node;
}
struct node* dequeue(struct node** queue, int *front){
	return (queue[(*front)++]);
}
void print_levelorder_q(struct node* root ){
	int front =0;
       	int rear =-1;
	struct node* temp = root;
	struct node** queue = (struct node**)malloc(sizeof(struct node*)*MAX_Q_SIZE);
	
	while(temp!=NULL){
		printf("%d ", temp->data);
		enqueue(temp->left, &rear, queue);
		enqueue(temp->right, &rear, queue);
		temp = dequeue(queue, &front);
	}
}
int main(){
	struct node* root = newnode(1);
	root->left = newnode(2);
	root->right = newnode(3);
	root->left->left = newnode(4);
	root->left->right = newnode(5);
	print_levelorder_q(root);
	return 0;
}
