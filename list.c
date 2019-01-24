#include "headers/list.h"

extern int writeBacks[2];

// Create a new list
List * newList(){
    List * list = malloc(sizeof(List));
    *list = (List){0};
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return list;
}

// Create a new list node
Node * newNode(int page, char rw, int pid){
    Node * node = malloc(sizeof(Node));
    node->page = page;
    node->dirty = 0;
    node->pid = pid;
    node->next = NULL;
    return node;
}

// Create a new list node based on the values of a given list node
Node * copyNode(Node * original){
    Node * node = malloc(sizeof(Node));
    node->page = original->page;
    node->dirty = original->dirty;
    node->pid = original->pid;
    node->next = NULL;
    return node;
}

// Add a new list node to a given list
void addToList(List * list, int page, char rw, int pid){
    if(list->first == NULL){
        // If list is empty, add it to the start of the list
        list->first = newNode(page,rw,pid);
        list->last = list->first;
    }
	else{
        // If list is not empty, add it to the end of the list
		list->last->next = newNode(page,rw,pid);
        list->last = list->last->next;
	}
    list->length++;
}

// Add a copy of a given node to a list
void addNodeToList(List * list, Node * node){
    if(list->first == NULL){
        list->first = copyNode(node);
        list->last = list->first;
    }
	else{
		list->last->next = copyNode(node);
        list->last = list->last->next;
	}
    list->length++;
}

// Flush all the pages of a certain process from the given list
List * flushList(List * list, int pid){
    // If list is empty, there is nothing to do
    if(list->first == NULL){
        return list;
    }

    // Create a new list that will contain
    // only the nodes that must not be flushed
    List * flushed = newList();

    // Go through the given list and add all the pages that
    // don't belong to the given process to a new list
    Node * node = list->first;
    while(node != NULL){
        if(node->pid != pid)
            addNodeToList(flushed, node);
        else if(node->dirty == 1)
            writeBacks[pid]++;
        node = node->next;
    }

    // Delete the old list and return the new, flushed list
    deleteNodes(list->first);
    free(list);

    return flushed;
}

// Check if a given page is present in a list
int isInList(List * list, int page, int pid){
    if(list->first == NULL){
        return 0;
    }

    Node * node = list->first;
    while(node != NULL){
        if(node->page == page && node->pid == pid) return 1;
        node = node->next;
    }

    return 0;
}

// Change the dirty bit of a page in a list to 1
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

// Given a node, delete it and all the nodes that come after it
void deleteNodes(Node * node){
    if(node->next != NULL)
        deleteNodes(node->next);

    free(node);
}

// Delete the given list
void deleteList(List * list){
    clearList(list);
    free(list);
}

// Empty the contents of a given list
void clearList(List * list){ 
    if(list->first == NULL){ 
        return; 
    } 
 
    deleteNodes(list->first); 

    list->first = NULL; 
    list->last = NULL; 
    list->length = 0; 
}
