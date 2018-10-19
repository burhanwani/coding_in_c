#include<stdio.h>
#include<stdlib.h>
//implementing queue using two stacks. Method: enqueue normally like stack, dequeue by copying one stack to another and popping the last element. 
struct stack{
	int capacity;
	int top;
	int* arr;
};

struct queue_stack{
	struct stack stack_1;
	struct stack stack_2;
}

int is_full(struct stack* p){
	if(p->top == (p->capacity-1)){
		return 1;
	}else
		return 0;
}
int is_empty(struct stack* p){
	if(p->top == -1)
		return 1;
	else 
		return 0;
}

void push(int x, struct stack* p){
	if(is_full(p)){
		printf("stack is full");
		return;
	}
	p->arr[++(p->top)]= x;
}

int pop(struct stack* p){
	if(is_empty(p)){
		printf("stack is empty");
		return -1;
	}
	return (p->arr[--(p->top)]);
}

void print_stack(struct stack* p){
	int top = p->top;
	while(top !=-1){
		printf("%d \n", p->arr[top--]);
	}
}

void enqueue_stack(struct queue* q, int data){
	push(q->stack_1, data);
}
//at any point we can have two stacks half filled with data. we will push in one and pop from another. 
int dequeue_stack(struct queue* q){
	int x;
	if(pop(q->stack_1) == -1){
		return -1;
	}
	if(is_empty(q->stack_2)){
		while(!is_empty(q->stack_1)){
			x = pop(q->stack_1);
			push(q->stack_2, x);
		}
	}
	x = pop(q->stack_2);
	return x;
}

int main(){
	int capacity = 20;
	/*
	int *array = (int*)malloc(capacity);
	struct stack my_stack;
	my_stack.top =-1;
	my_stack.capacity = capacity;
	my_stack.arr = array;
	push(1, &my_stack);
	push(2, &my_stack);
	print(&my_stack);
	*/
	struct queue_stack my_queue;
	my_queue.stack_1.capacity = capacity;
	my_queue.stack_1.top = -1;
	my_queue.stack_1.arr = (int*)malloc(capacity);
	my_queue.stack_2.capacity = capacity;
	my_queue.stack_2.top = -1;
	my_queue.stack_2.arr = (int*)malloc(capacity);
	enqueue_stack(my_queue, 1);
	enqueue_stack(my_queue, 2);
	enqueue_stack(my_queue, 3);
	enqueue_stack(my_queue, 4);
	dequeue_stack(my_queue);
	enqueue_stack(my_queue, 5);



	return 0;
}
