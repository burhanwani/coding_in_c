#include<stdio.h>
#include<stdlib.h>
//stack and queue implementation using linked list 
struct stack{
	int data;
	struct stack* next;
};

struct queue{
	int data;
	struct queue* next;
};

void push_s (struct stack** top, int data){
	struct stack* new = (struct stack*)malloc(sizeof(struct stack));
	new->data = data;
	new->next= *top;
	*top = new;
}

int pop_s(struct stack** top){
	if(*top == NULL)
		return -1;
	struct stack* temp = *top;
	*top = temp->next;
	free(temp);
	return 0;
}

void enqueue(int data, struct queue** rear, struct queue** front){
	struct queue* new = (struct queue*)malloc(sizeof(struct queue));
        new->data = data;
	new->next = NULL;
	if(*front == NULL)
		*front = new;
	if(*rear == NULL)
		*rear = new;
	else
		(*rear)->next = new;
	*rear = new;
}	

int dequeue(struct queue** rear, struct queue** front){
	struct queue* temp = *front;
	if(*front == NULL)
		return -1;
	if(*front == *rear){
		free(*front);
		*front = NULL;
		*rear = NULL;
	}else{
		*front = (*front)->next;
		free(temp);
	}
	return 0;
}
void print(struct queue* p){
	while(p!=NULL){
		printf("%d", p->data);
		p  = p->next;
	}
}

int main(){
	struct queue* rear = NULL;
       	struct queue* front = NULL;
	enqueue(1, &rear, &front);
	dequeue(&rear, &front);
	enqueue(2, &rear, &front);
	enqueue(3, &rear, &front);
	print(front);

}

