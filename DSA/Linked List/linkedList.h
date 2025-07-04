#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int element;
    struct node* next;
    struct node* prev;
} node;

typedef struct 
{
    // declare head, tail, cur and other variables you need
    node* head;
    node* tail;
    node* cur;
} linkedList;

void init(linkedList* list)
{
    // implement initialization
    list->head = NULL;
    list->cur = NULL;
    list->tail = NULL;
}

void free_list(linkedList* list)
{
    // implement destruction of list
    while(list->head != NULL) {
        node* temp = list->head->next;
        free(list->head);
        list->head = temp;
    }
    list->cur = NULL;
    list->tail = NULL;
}

void print(linkedList* list)
{
    // implement list printing
    if(list->head == NULL) {
        printf("[.]\n");
    }
    else {
        printf("[ ");
        node* temp = list->head;
        while(temp != NULL) {
            if(temp == list->cur) {
                printf("%d| ", temp->element);
            }
            else printf("%d ", temp->element);
            temp = temp->next;
        }
        printf("]\n");
    }
}

void insert(int item, linkedList* list)
{
    // implement insert function
    node* newNode = (node*)malloc(sizeof(node));
    newNode->element = item;
    newNode->next = NULL;
    newNode->prev = NULL;
    if(list->head == NULL) {
        list->head = list->cur = list->tail = newNode;        
    }
    else {
        newNode->next = list->cur->next;
        newNode->prev = list->cur;        
        if(list->cur->next) list->cur->next->prev = newNode;        
        else list->tail = newNode;
        list->cur->next = newNode;

        list->cur = newNode;
    }
    print(list);
}

int delete_cur(linkedList* list)
{
    // implement deletion of current index function
    if(list->cur) {
        int res = list->cur->element;
        node* temp = list->cur;
        if(temp->prev) {
            temp->prev->next = temp->next;
        }
        else {
            list->head = temp->next;
        }
        if(temp->next) {
            temp->next->prev = temp->prev;
        }
        else {
            list->tail = temp->prev;    
        }

        if(list->cur->next)list->cur = list->cur->next;
        else list->cur = list->cur->prev;
        free(temp);
        print(list);
        return res;   
    }
    else printf("No element left to delete\n");
}

void append(int item, linkedList* list)
{
    // implement append function
    node* newNode = (node*)malloc(sizeof(node));
    newNode->element = item;
    newNode->next = NULL;
    newNode->prev = NULL;
    if(list->head) {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    else {
        list->head = list->tail = list->cur = newNode;
    }
    print(list);
}

int size(linkedList* list)
{
    // implement size function
    int size = 0;
    node* temp = list->head;
    while(temp != NULL) {
        temp = temp->next;
        size++;
    }
    return size;
}

void prev(int n, linkedList* list)
{
    // implement prev function
    while(n-- && list->cur != list->head) {
        list->cur =  list->cur->prev;
    }
    print(list);
}

void next(int n, linkedList* list)
{
    // implement next function
    while(n-- && list->cur != list->tail) {
        list->cur =  list->cur->next;
    }
    print(list);
}

int is_present(int n, linkedList* list)
{
    // implement presence checking function
    node* temp = list->head;
    while(temp != NULL) {
        if(temp->element == n) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void clear(linkedList* list)
{
    // implement list clearing function
    free_list(list);
    init(list);
    print(list);
}

void delete_item(int item, linkedList* list)
{
    // implement item deletion function
    node* t1 = list->head;
    while(t1 != NULL) {
        if(t1->element == item) {
            node* t2 = list->cur;
            if(t1 == list->cur) {
                delete_cur(list);
            }
            else {
                // list->cur = t1;
                // delete_cur(list);
                // list->cur = t2;
                if(t1->prev) t1->prev->next = t1->next;
                else list->head = t1->next;
                if(t1->next) t1->next->prev = t1->prev;
                else list->tail = t1->prev;
                free(t1);
                print(list);
            }
            return;
        }
        t1 = t1->next;
    }
    printf("%d not found\n", item);
}

void swap_ind(int ind1, int ind2, linkedList* list)
{
    // implement swap function
    node* t1 = list->head;
    node* t2 = list->head;

    while(ind1--) {
        t1 = t1->next;
    }
    while(ind2--) {
        t2 = t2->next;
    }

    int temp = t1->element;
    t1->element = t2->element;
    t2->element = temp;
    print(list);
}

// you can define helper functions you need
