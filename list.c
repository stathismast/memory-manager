#include "list.h"

List * newList(){
    List * list = malloc(sizeof(List));
    *list = (List){0};
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return list;
}

Node * newNode(int page, char rw, int pid){
    Node * node = malloc(sizeof(Node));
    node->page = page;
    node->dirty = 0;
    node->pid = pid;
    node->next = NULL;
    return node;
}

void addToList(List * list, int page, char rw, int pid){
    if(list->first == NULL){
        list->first = newNode(page,rw,pid);
        list->last = list->first;
    }
	else{
		list->last->next = newNode(page,rw,pid);
        list->last = list->last->next;
	}
    list->length++;
}

void emptyList(List * list){
    if(list->first == NULL){
        return;
    }

    deleteNodes(list->first);

    list->first = NULL;
    list->last = NULL;
    list->length = 0;
}

// Flush all the pages of a certain process from the given list
List * flushList(List * list, int pid){
    if(list->first == NULL){
        return list;
    }

    List * flushed = newList();

    Node * node = list->first;
    while(node != NULL){
        if(node->pid != pid){
            char rw;
            if(node->dirty == 1)
                rw = 'W';
            else rw = 'R';
            addToList(flushed, node->page, rw, node->pid);
        }
        node = node->next;
    }

    deleteNodes(list->first);
    free(list);

    return flushed;
}

int isInList(List * list, int page){
    if(list->first == NULL){
        return 0;
    }

    Node * node = list->first;
    while(node != NULL){
        if(node->page == page) return 1;
        node = node->next;
    }

    return 0;
}

void changeDirtyBit(List * list, int page){
    if(list->first == NULL){
        return;
    }

    Node * node = list->first;
    while(node != NULL){
        if(node->page == page) node->dirty = 1;
        node = node->next;
    }
}

void deleteNodes(Node * node){
    if(node->next != NULL)
        deleteNodes(node->next);

    free(node);
}

void printList(List * list){
    if(list->first == NULL){
        printf("List is empty.\n");
        return;
    }

    printf("Length: %d\n", list->length);
    Node * node = list->first;
    while(node != NULL){
        printf("%d. %d %d\n", node->pid, node->dirty, node->page);
        node = node->next;
    }
}

char notEmpty(List * list){
    return !(list->first == NULL);
}
