
// C++ program to print DFS traversal from
// a given vertex in a  given graph
#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* global_stack;
// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*) malloc(stack->capacity * sizeof(int));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{   return stack->top == stack->capacity - 1; }

int isEmpty(struct Stack* stack)
{   return stack->top == -1;  }

// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, int item)
{
    if (isFull(stack))
    return;
    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}

// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack)
{
    if (isEmpty(stack))
    return -32768;
    return stack->array[stack->top--];
}

struct node {
    int value;
    struct node* next;
};

struct list {
    struct node* head;
};

struct graph{
    struct list * adj_list;
    int V;
};

struct graph* create_graph(int V)
{
    struct graph* my_graph = (struct graph*)malloc(sizeof(struct graph));
    my_graph->V = V;
    my_graph->adj_list = (struct list*)malloc(V*sizeof(struct list));
    int i;
    for(i=0;i<V;i++){
        my_graph->adj_list[i].head = NULL;
    }
    return my_graph;
}

struct node* new_node(int val){
    struct node* newn = (struct node*)malloc(sizeof(struct node));
    newn->value = val;
    newn->next = NULL;
    return newn;
}

void addEdge(struct graph* my_graph, int src, int dest)
{
    struct node* new_n = new_node(dest);
    struct node* new_nn = new_node(src);
    //make connection from src to dest
    struct node* temp = my_graph->adj_list[src].head;
    while(temp!=NULL){
        temp = temp->next;
    }
    temp->next = new_n;
    //make connection from dest to src
    temp = my_graph->adj_list[dest].head;
    temp = new_nn;
    while(temp!=NULL){
        temp=temp->next;
    }
    temp->next = new_nn;
}

void DFSUtil(int v, int* visited, struct graph* my_graph)
{
    // Mark the current node as visited and
    // print it
    struct node* temp;
    int foo;
    visited[v] = 1;
    printf("%d \n", v);
    int count=0;
    temp = my_graph->adj_list[v].head;
    
    // Recur for all the vertices adjacent
    // to this vertex
    
    while(temp!=NULL){
        push(global_stack,temp->value);
        temp=temp->next;
        count++;
    }
    while(count){
        foo = pop(global_stack);
        if (!visited[foo])
        DFSUtil(foo, visited, my_graph);
        count--;
    }
}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void DFS(int v, int V, struct graph* my_graph)
{
    // Mark all the vertices as not visited
    int *visited = (int*)malloc(V*sizeof(int));
    for (int i = 0; i < V; i++)
        visited[i] = 0;
    
    // Call the recursive helper function
    // to print DFS traversal
    DFSUtil(v, visited, my_graph);
}

int main()
{
    // Create a graph given in the above diagram
    struct graph * my_graph = create_graph(5);
    global_stack = createStack(100);
    addEdge(my_graph, 0, 1);
    addEdge(my_graph, 0, 2);
    addEdge(my_graph, 1, 2);
    addEdge(my_graph, 2, 0);
    addEdge(my_graph, 2, 3);
    addEdge(my_graph, 3, 3);
    addEdge(my_graph, 3, 5);
    
    printf("Following is Depth First Traversal starting from vertex 2) \n");
    DFS(2, 5, my_graph);
    
    return 0;
}
