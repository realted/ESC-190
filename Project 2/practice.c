#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*

typedef struct Arraylist{
    int *data;
    int size;
    int capacity;
} ArrayList;

void new_AL_list(ArrayList **p_AL, int size){
    (*p_AL) = (ArrayList*)malloc(sizeof(ArrayList));
    (*p_AL)->capacity = size;
    (*p_AL)->size = 0;
    (*p_AL)->data = (int*)malloc(sizeof(int)*size);
}

void AL_enqueue(ArrayList *my_list, int elem){
    if (my_list->size == my_list->capacity){
        my_list->capacity *= 2;
        my_list->data = (int*)realloc(my_list->data, sizeof(int)*my_list->capacity);
    }
    my_list->data[my_list->size] = elem;
    my_list->size++;
}

void AL_dequeue(ArrayList *my_list){
    int loc = 0;
    while(my_list->data[loc] != 0){
        loc++;
    }
    my_list->data[loc] = 0;
}

int main(){
    ArrayList** list; 
    new_AL_list(list, 4);
    AL_enqueue(*list, 3);
    AL_enqueue(*list, 5);
    AL_enqueue(*list, 6);
    AL_dequeue(*list);
    AL_dequeue(*list);
    AL_enqueue(*list, 9);
    
    printf("[");
    for (int i=0; i< ((*list)->size); i++){
        printf("%d ", (*list)->data[i]);
    }
    printf("]");
}

*/



#include <stdlib.h>
#include <stdio.h>

typedef struct Con{
    double weight;
    struct Node *node;
} Con;


typedef struct Node {
    int data;
    int num_neighbours;
    int num_cons;
    int visited;
    struct Con **connections;
    double dist_from_start;

} Node;


void create_node(int data, Node **p_node) {
    *p_node = malloc(sizeof(Node));
    (*p_node)->data = data;
    (*p_node)->connections = (void *)0;
    (*p_node)->num_cons = 0;
    (*p_node)->visited = 0;
    (*p_node)->dist_from_start = 10000000.0;
}

void add_neighbour(Node *node, Node *neighbour, double weight) {
    node->num_cons++;
    node->connections = realloc(node->connections, (node->num_cons) * sizeof(Con *));
    node->connections[node->num_cons - 1] = malloc(sizeof(Con));
    node->connections[node->num_cons - 1]->weight = weight;
    node->connections[node->num_cons - 1]->node = neighbour;
}



void add_to_visited(Node ***visited, int *p_n_visited, Node *node) {
    for(int i = 0; i < *p_n_visited; i++) {
        if ((*visited)[i] == node) {
            return;
        }
    }
    (*p_n_visited)++;
    *visited = (Node**)realloc(*visited, *p_n_visited * sizeof(Node *));
    (*visited)[*p_n_visited - 1] = node;
}

int was_visited(Node **visited, int n_visited, Node *node) {
    for(int i = 0; i < n_visited; i++){
        if (visited[i] == node){
            return 1;
        }
        else{
        }
    }
    return 0;
}


void dijkstra(Node *start, Node *end) {
    Node **visited = (void *)0; // visited = set([start])
    int num_visited = 0; // number of visited shit
    Node *current = start; // current might be the node we are dealing with
    add_to_visited(&visited, &num_visited, current);

    while (current != end) {
        double min_dist = 1000000000.0; // cur_dist
        Node *min_node = (void *)0;  // cur_v
        for(int i = 0; i < num_visited; i++){
            for (int j = 0; j < ((visited[i])->num_cons); j++){
                if (was_visited(visited, num_visited, (visited[i])->connections[j]->node) == 1){
                    continue;
                }
                if(min_dist > (visited[i])->dist_from_start + (visited[i])->connections[j]->weight){
                    min_dist = (visited[i])->dist_from_start + (visited[i])->connections[j]->weight;
                    min_node = (visited[i])->connections[j]->node;
                }
            }

        }
        current = min_node;
        current->dist_from_start = min_dist;
        add_to_visited(&visited, &num_visited, current);
    }
}


int main(){
    Node *a;
    Node *b;
    Node *c;
    Node *d;
    Node *e;
    Node *f;
    Node *g;
    Node *h;
    create_node(1, &a);
    create_node(2, &b);
    create_node(3, &c);
    create_node(4, &d);
    create_node(5, &e);
    create_node(6, &f);
    create_node(7, &g);
    create_node(8, &h);
    add_neighbour(a, b, 2);
    add_neighbour(a, d, 6);
    add_neighbour(b, e, 1);
    add_neighbour(d, e, 8);
    add_neighbour(c, e, 3);
    add_neighbour(a, c, 1);
    add_neighbour(e, f, 7);
    add_neighbour(e, g, 5);
    add_neighbour(f, h, 5);
    add_neighbour(g, h, 6);
    a->dist_from_start = 0;
    dijkstra(a, h);
    printf("%f\n", h->dist_from_start);
}

