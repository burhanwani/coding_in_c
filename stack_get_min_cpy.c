#include<stdio.h>
#include<stdlib.h>
//get min in 0(1) time
struct stack{
	int capacity;
	int top;
	int* arr;
};
struct stack aux_stack;
int min;

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
	if(x < min){
		aux_stack.arr[++(aux_stack.top)]= x;
		min = x;
	}
	p->arr[++(p->top)]= x;
}

int pop(struct stack* p){
	if(is_empty(p)){
		printf("stack is empty");
		return -1;
	}
	if(p->arr[p->top]== min){
		aux_stack.top--;
	}
	return (p->arr[--(p->top)]);
}

int get_min(){
	return aux_stack.arr[(aux_stack.top)];
}

void print_stack(struct stack* p){
	int top = p->top;
	while(top !=-1){
		printf("%d \n", p->arr[top--]);
	}
}



int main(){
	int capacity = 20;
	int *array1 = (int*)malloc(capacity);
	int *array2 = (int*)malloc(capacity);
	struct stack my_stack;
	int min_element;
	min = 200;
	my_stack.top =-1;
	my_stack.capacity = capacity;
	my_stack.arr = array1;
	aux_stack.top =-1;
	aux_stack.capacity = capacity;
	aux_stack.arr = array2;
	push(7, &my_stack);
	push(3, &my_stack);
	push(8, &my_stack);
	push(1, &my_stack);
	pop(&my_stack);
	min_element = get_min();
	printf(" smallest element %d", min_element);
	


	return 0;
}
