#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int *array;
    // declare variables you need
    int size;
    int capacity;
    int cur;
} arrayList;

void init(arrayList* list)
{
    // implement initialization
    list->size = 0;
    list->capacity = 2;
    list->cur = 0;
    list->array = (int*)malloc(sizeof(int)*list->capacity);
}

void free_list(arrayList* list)
{
    // implement destruction of list
    free(list->array);
}

void increase_capacity(arrayList* list)
{
    // implement capacity increase
    if(2*list->size > list->capacity) {
        int newCapacity = list->capacity*2;
        int *tempArray = (int*)realloc(list->array, sizeof(int)*newCapacity);    
        if(tempArray != NULL) {
            list->array = tempArray;
            printf("Capacity increased from %d to %d\n", list->capacity, newCapacity);
            list->capacity = newCapacity;
        }
    }
}

void decrease_capacity(arrayList* list)
{
    // implement capacity decrease
    if(4*list->size < list->capacity) {
        int newCapacity = list->capacity/2;
        int *tempArray = (int*)realloc(list->array, sizeof(int)*newCapacity);    
        if(tempArray != NULL) {
            list->array = tempArray;
            printf("Capacity decreased from %d to %d\n", list->capacity, newCapacity);
            list->capacity = newCapacity;
        }
    }
}

void print(arrayList* list)
{
    // implement list printing
    if(list->size == 0) {
        printf("[.]\n");
        return;
    }
    printf("[ ");
    for(int i = 0; i < list->size; i++) {
        if(i+1 == list->cur) {
            printf("%d| ", *(list->array + i));
        }
        else printf("%d ", *(list->array + i));
    }
    printf("]\n");
}

void insert(int item, arrayList* list)
{
    // implement insert function
    list->size++;
    increase_capacity(list);
    for(int i = list->size-1; i >= list->cur; i--) {
        list->array[i] = list->array[i-1];
    }
    list->array[list->cur] = item;
    list->cur++;    
    print(list);
}

int delete_cur(arrayList* list)
{
    // implement deletion of curent index function
    if(list->cur) {
        int res = list->array[list->cur-1];
        for(int i = list->cur-1; i < list->size-1; i++) {
            list->array[i] = list->array[i+1];
        }
        if(list->cur == list->size) {
            list->cur--;
        }
        list->size--;
        decrease_capacity(list);
        print(list);
        return res;
    }    
    else printf("No element left to delete\n");
}

void append(int item, arrayList* list)
{
    // implement append function
    if(list->size == 0) {
        insert(item, list);
        return;
    }
    list->size++;
    increase_capacity(list);
    list->array[list->size-1] = item;
    print(list);
}

int size(arrayList* list)
{
    // implement size function
    return list->size;
}

void prev(int n, arrayList* list)
{
    // implement prev function
    while(n) {
        n--;
        if(list->cur > 1) {
            list->cur--;
        }
        else {
            break;
        }
    }
    print(list);
}

void next(int n, arrayList* list)
{
    // implement next function
    while(n) {
        n--;
        if(list->cur < list->size) {
            list->cur++;
        }
        else {
            break;
        }
    }
    print(list);    
}

int is_present(int n, arrayList* list)
{
    // implement presence checking function
    for(int i = 0; i < list->size; i++) {
        if(list->array[i] == n) return 1;
    }
    return 0;
}

void clear(arrayList* list)
{
    // implement list clearing function
    free(list->array);
    // list->size = 0;
    // list->cur = 0;
    // list->capacity = 2;
    // list->array = (int*)malloc(sizeof(int)*list->capacity);
    init(list);
    print(list);
}

void delete_item(int item, arrayList* list)
{
    // implement item deletion function
    for(int i = 0; i < list->size; i++) {
        if(list->array[i] == item) {
            if(i+1<list->cur) {
                list->cur--;
            }
            for(; i < list->size-1; i++) {
                list->array[i] = list->array[i+1];
            }
            list->size--;
            decrease_capacity(list);
            print(list);
            return;
        }
    }    
    printf("%d is not found\n", item);  
}

void swap_ind(int ind1, int ind2, arrayList* list)
{
    // implement swap function
    int temp = list->array[ind1];
    list->array[ind1] = list->array[ind2];
    list->array[ind2] = temp;
    print(list);
}

// you can define helper functions you need