#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int date;
    double min;
    double max;
    struct node * next;
} node_t;

/* Prints a table with date min and max values */
void print_list(node_t * head);

/* Initiates a new node_t */
struct node* newNode(int new_date, double new_min, double new_max);

/* Inserts a node in a sorted linked list */
void insert(node_t** head_r, node_t * newnode);

/* Deletes a node from linked list */
void delete(node_t** head_r, int index);

int main(){
    // declare variables
    char command;
    int date;
    double min, max;
    node_t * head = NULL;

    // declarations for reading input
    char input[100];
    const char s[2] = " ";
    char *token;

    do { // read input until 'Q' command entered
        printf("Enter command: ");
        fgets(input, 100, stdin);
        token = strtok(input, s);
        command = *token;

        switch(command){
            case 'A':
                // read rest of input
                token = strtok(NULL, s);
                if(token == NULL){
                    printf("Invalid input...\n");
                    break;
                }
                date = atoi(token);
                if(date>31 || date<1){
                    printf("Check your calender...\n");
                    break;
                }

                token = strtok(NULL, s);
                if(token == NULL){
                    printf("Invalid input...\n");
                    break;
                }
                min = atof(token);

                token = strtok(NULL, s);
                if(token == NULL){
                    printf("Invalid input...\n");
                    break;
                }
                max = atof(token);

                if(min > max){
                    printf("Check your min/max values...\n");
                }

                node_t * newnode = newNode(date, min, max);
                insert(&head, newnode);
                break;
            case 'D':
                // read rest of input
                token = strtok(NULL, s);
                if(token == NULL){
                    printf("Invalid input...\n");
                    break;
                }
                date = atoi(token);

                printf("date: %d\n", date);

                delete(&head, date);
                break;
            case 'P':
                print_list(head);
                break;
            default:
                if(command != 'Q') printf("Invalid input...\n");
                break;
        }
    }while(command != 'Q');

    return 0;
}

void insert(node_t** head_r, node_t * newnode){
    node_t * current = *head_r;
    if(current == NULL || current->date > newnode->date){
        newnode->next = current;
        *head_r = newnode;
    } else if(current->date == newnode->date){
        current->min = newnode->min;
        current->max = newnode->max;
    } else { 
        while (current->next != NULL && current->next->date < newnode->date){ 
            current = current->next; 
        } 
        if(current->next == NULL){
            current->next = newnode;
        } else if(current->next->date == newnode->date){
            current->next->min = newnode->min;
            current->next->max = newnode->max;
        } else {
            newnode->next = current->next; 
            current->next = newnode;
        }
    }
}

struct node* newNode(int new_date, double new_min, double new_max) { 
    struct node * newnode = (node_t *)malloc(sizeof(node_t)); 
    newnode->date = new_date;
    newnode->max = new_max;
    newnode->min = new_min;
    newnode->next = NULL; 
    return newnode; 
} 

void print_list(node_t * head){
    printf("%2s %5s %10s\n", "day", "min", "max");
    while(head != NULL){
        printf("%2d %10f %10f\n", head->date, head->min, head->max);
        head = head->next;
    }
}

void delete(node_t** head_r, int index){
    node_t * current = *head_r;
    if(current == NULL){
        printf("List is empty...\n");
    }else if(current->date == index){
        *head_r = current->next;
    }else if(current->next == NULL){
        printf("Date does not exist...\n");
    } else {  
        while (current->next != NULL && current->next->date < index){ 
            current = current->next; 
        }
        if(current->next == NULL){
            printf("Date does not exist...\n");
        } else if(current->next->date == index){
            current->next = current->next->next;
        } else {
            printf("Date does not exist...\n");
        }
    }
    free(current);
}