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


struct node* newnode(int data){
	struct node* new = (struct node*)malloc(sizeof(struct node*));
	new->data = data;
	new->left = NULL;
	new->right = NULL;
	return new;
}
//for every node check if the difference in height of the left and right subtree is at most 1. 
// nlogn time complexity. 
int check_balanced(struct node* root){
	int height_diff;
	if (root == NULL)
		return 1;
	height_diff = height(root->left) - height(root->right);
	if (height_diff > 1)
		return 0;
	else 
		return ( check_balanced(root->left) && check_balanced(root->right));


}
//this function will not only calculate the height of a node but also check if that node is balanced or not
int check_height (struct node* root){
	int lheight, rheight;
	if (root == NULL){
		return 0;
	}
	lheight = check_height(root->left);
	if (lheight == -1)
		return -1;
	rheight = check_height(root->right);
	if (rheight == -1)
		return -1;
	if ((lheight - rheight) > 1){
	       return -1;
	} else {
 		if (lheight > rheight){
			return (lheight +1);
		}else 
			return (rheight +1);
	}		

}

int check_balanced_2(struct node* root){
	if (check_height(root) != -1)
		return 1;
	else 
		return 0;
}

int main(){
	struct node* root = newnode(1);
	root->left = newnode(2);
	root->right = newnode(3);
	root->left->left = newnode(4);
	root->left->right = newnode(5);
	return 0;
}
