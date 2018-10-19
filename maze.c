
// find a path in a maze from source to destination.
#include <stdio.h>
#include <stdlib.h>

#define NO_OF_COLUMNS 5
#define NO_OF_ROWS 5
int maze [NO_OF_ROWS][NO_OF_COLUMNS] = {{0,0,1,0,0},{0,0,0,0,0},{0,0,0,1,0},{1,1,0,1,1},{0,0,0,0,0}};
int visited[NO_OF_ROWS][NO_OF_COLUMNS] = {0};
struct node {
    int value;
    int row_nu;
    int col_nu;
    struct node* next;
};

struct list {
    struct node* head;
};

struct graph{
    struct list * adj_list;
    int V;
};

struct Stack
{
    int top;
    unsigned capacity;
    struct node** array;
};

struct Stack* global_stack;
// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct node**) malloc(stack->capacity * sizeof(struct node*));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{   return stack->top == stack->capacity - 1; }

int isEmpty(struct Stack* stack)
{   return stack->top == -1;  }

// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, struct node* item)
{
    if (isFull(stack))
    return;
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack.  It decreases top by 1
struct node* pop(struct Stack* stack)
{
    if (isEmpty(stack))
    return 0;
    return stack->array[stack->top--];
}



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

struct node* new_node(int row, int col){
    struct node* newn = (struct node*)malloc(sizeof(struct node));
    newn->value = maze[row][col];
    newn->row_nu = row;
    newn->col_nu = col;
    newn->next = NULL;
    return newn;
}

void addEdge(struct graph* my_graph, int src_row, int src_col, int dest_row, int dest_col)
{
    struct node* new_n = new_node(dest_row, dest_col);
    //make connection from src to dest
    struct node* temp = my_graph->adj_list[src_row*NO_OF_COLUMNS + src_col].head;
    if(temp == NULL){
        my_graph->adj_list[src_row*NO_OF_COLUMNS + src_col].head = new_n;
    }else {
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = new_n;
    }
   
}

int DFSUtil(int src_row, int src_col, int dest_row, int dest_col,struct graph* my_graph)
{
    // Mark the current node as visited and
    // print it
    struct node* temp;
    struct node* foo;
    if (src_row == dest_row && src_col == dest_col){
        printf("fouund the path \n");
        return 1;
    }
    visited[src_row][src_col] = 1;
    int count=0;
    temp = my_graph->adj_list[src_row*NO_OF_COLUMNS + src_col].head;
    
    // Recur for all the vertices adjacent
    // to this vertex
    
    while(temp!=NULL){
        if(temp->value == 0){
            push(global_stack,temp);
            count++;
        }
        temp=temp->next;
    }
    while(count){
        foo = pop(global_stack);
        if (!visited[foo->row_nu][foo->col_nu])
        if(DFSUtil(foo->row_nu, foo->col_nu, dest_row, dest_col, my_graph) == 1){
            return 1;
        }
        count--;
    }
    return 0;
}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void DFS(int src_row, int src_col, int dest_row, int dest_col,  int V, struct graph* my_graph)
{
    // Call the recursive helper function
    // to print DFS traversal
    DFSUtil(src_row, src_col, dest_row, dest_col, my_graph);
    
}


int is_safe(int neigh_row, int neigh_col){
    if (neigh_row>=0 && neigh_row < NO_OF_ROWS && neigh_col >=0 && neigh_col < NO_OF_COLUMNS){
        return 1;
    }else{
        return 0;
    }
}
int main()
{
    
    int start_row = 0;
    int start_col = 4;
    int end_row = 3;
    int end_col = 2;
    int row;
    int col;
    int neigh_col;
    int neigh_row;
    // Create a graph given in the above diagram
    struct graph * my_graph = create_graph(NO_OF_ROWS*NO_OF_COLUMNS);
    global_stack = createStack(100);
    //first create a graph of all the edges. Note no cross or diagonal neighbours
    int i;
    int j;
    for(row=0;row<NO_OF_ROWS;row++){
        for(col=0;col<NO_OF_COLUMNS;col++){
            for(i=-1;i<2;i++){
                for(j=-1;j<2;j++){
                    neigh_row = row +i;
                    neigh_col = col +j;
                    if(is_safe(neigh_row, neigh_col)){
                        if(!(abs(neigh_col - col)>0 && abs(neigh_row - row)>0) && !(neigh_row == row && neigh_col == col)){ // no diagonal neighbours
                            addEdge(my_graph, row, col, neigh_row, neigh_col);
                        }
                    }
                }
            }
        }
    }
    
    printf("Following is Depth First Traversal starting from vertex 2) \n");
    DFS(start_row,start_col,end_row, end_col, NO_OF_ROWS*NO_OF_COLUMNS, my_graph);
    
    return 0;
}
