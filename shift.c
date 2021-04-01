#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct DLL {
    unsigned size;
    struct Node* current;
} DLL;

DLL* DLL_create() {
    DLL* tmp = (DLL*)malloc(sizeof(DLL));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->size = 0;
    tmp->current = NULL;
    return tmp;
}

void DLL_delete(DLL** list) {
    if ((*list)->size) {
        Node* tmp = (*list)->current;
        Node* following;
        tmp->prev->next = NULL;
        while (tmp == NULL) {
            following = tmp->next;
            free(tmp);
            tmp = following;
            (*list)->size--;
        }
    }
    free(*list);
}

void push(DLL* list, int val) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->value = val;
    tmp->next = tmp->prev = NULL;
    if (list->current) {
        if (list->size == 1) {
            tmp->prev = tmp->next = list->current;
            list->current->next = list->current->prev = tmp;
        } else {
            Node *previous = list->current->prev;
            previous->next = tmp;
            tmp->prev = previous;
            tmp->next = list->current;
            list->current = tmp;
        }
    } else {
        list->current = tmp;
    }
    list->size++;
}

int pop(DLL* list) {
    if (list->size == 1) {
        int retval = list->current->value;
        free(list->current);
        return retval;
    } else if (list->size == 2) {
        int retval = list->current->value;
        list->current = list->current->next;
        free(list->current->next);
        return retval;
    } else if (list->size > 2) {
        Node *first = list->current->next;
        Node *second = list->current->prev;
        int retval = list->current->value;
        free(list->current);
        list->current = first;
        first->prev = second;
        second->next = first;
        list->size--;
        return retval;
    } else {
        printf("Empty list!\n");
        return 0;
    }
}
void shift(DLL* list, int n){
	 Node *tmp=list->current;
	 Node *ptr = tmp;
	     if(n>=0){
	         tmp->prev->next=tmp->next;
	         tmp->next->prev = tmp->prev;
	         int i;
	         for(i=0;i<n;i++){
		         ptr = ptr->next;
	             }
	         tmp->prev=ptr;
	         tmp->next=ptr->next;
	         if (ptr->next) {
                 ptr->next->prev = tmp;
                }
             ptr->next = tmp;
        
	 }
	     else{
	         tmp->prev->next=tmp->next;
	         tmp->next->prev = tmp->prev;
	         
	         int i;
	         for(i=0;i<abs(n);i++){
		         ptr = ptr->prev;
	             }
	         tmp->prev=ptr;
	         tmp->next=ptr->next;
	         if (ptr->next) {
                 ptr->next->prev = tmp;
                }
             ptr->next = tmp;
	     }
	}

void print(DLL *list) {
    Node *tmp = list->current;
    int i;
    for (i=0;i<list->size;i++){
    	printf("%d,",tmp->value);
    	tmp = tmp->next;
    }
    printf("\n");
}
void printy(DLL *list) {
    Node *tmp = list->current;
    printf("%d\n",tmp->value);

}
Node * shift1(DLL* list, int n){
    Node *tmp = list->current;
    int i;
    if(n>=0){
    for(i=0;i<n;i++){
        tmp=tmp->next;
    }
    }
    else{
        for(i=0;i<abs(n);i++){
        tmp=tmp->prev;
    }
    }
    return tmp;
}

void main() {
    DLL* List = DLL_create();
    push(List, 4);
    push(List, 8);
    push(List, 16);
    push(List, 32);
    push(List, 7);
    push(List, 5);
    print(List);
    shift(List,2);
    print(List);
    DLL_delete(&List);
}
