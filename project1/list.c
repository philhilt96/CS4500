#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/* Allocate space for a new list and set head to NULL.
 * Return new list is successful, else NULL. */
list* create_list() {
    // Allocate memory for list
    list* list_ptr = (list*)malloc(sizeof(list));

    // Check if allocation was successful
    if (list_ptr != NULL) {
        // Set head to NULL
        list_ptr->head = NULL;
        return list_ptr;
    }
    // No memory space available
    else {
        return NULL;
    }
}

/* Allocate new node and copy string from item to this node. Add this new
 * node to end of list. Returns 0 if successful, non-zero otherwise. */
int add_to_list(list* ll, char* item) {
    // Allocate new node
    node* new_node = (node*)malloc(sizeof(node));

    // Check if memory is available
    if (new_node == NULL) {
	return 1;
    }

    node* last_node = ll->head;
    // insert string from item as node data
    new_node->item = item;
    // make node point to null
    new_node->next = NULL;
    // if list is empty make new node the head 
    if (ll->head == NULL) {
        ll->head = new_node;
        return 0;
    }
    // traverse list until at the last node and add node
    //node* last = ll->head; 
    while (last_node->next != NULL) {
        last_node = last_node->next;
    }
    last_node->next = new_node;
    return 0;
}

/* Removes the head of the list ll, extracts the string stored in the head,
 * returns a pointer to this string. Also frees removed head node. */
char* remove_from_list(list* ll) {
    // retrieve item in head and point head to next node
    char* returnStr = ll->head->item;
    node* temp = ll->head;
    ll->head = ll->head->next;
    // free unused memory
    free(temp);
    return returnStr;
}

/* Prints every string in each node of the list ll, with a new line
 * character at the end of each string */
void print_list(list* ll) {          
     //Check if list is NULL
     if(ll != NULL){
        node* current_node = ll->head;
        while (current_node != NULL) {
    		printf(" %s\n", current_node->item);
        	current_node = current_node->next;
    	}
     }else{
	printf("%s\n", "List is NULL");
     }
}

/* Flushes (clears) the entire list and re-initializes the list. The passed
 * pointer ll should still point to a valid, empty list when this function
 * returns. Any memory allocated to store nodes in the list should be freed.
 */
void flush_list(list* ll) {
    // Assign head to current node
    node* current = ll->head;
    node* previous = NULL;

    // Loop until the entire list has been cleared
    while (current != NULL) {
	// Increment pointers
	previous = current;
        current = current->next;

	// Free memory of the previous node
	free(previous);
	previous = NULL;
    }

    // Free remaining temp variables and head
    free(current);

    // Re-initialize the list
    ll->head = NULL;
}

/* De-alllocates all data for this list. Ensure all memory allocated for the list
* ll is freed, including any allocated strings and list ll itself. */
void free_list(list **ll){
        // Assign head to current node
	node* current = (*ll)->head;
	node* previous = NULL;

	
	//Loop until entire list has been cleared
	while(current != NULL){
		//Increment pointers
		previous = current;
		current = current->next;
		
		//Free memory of previous node
		previous = NULL;
		free(previous);
	}
	

	//Free Remaining temp variable and head
	current = NULL;	
	free(current);

	//Free list struct and set data to null
	(*ll)->head = NULL;
	free((*ll)->head);
	(*ll) = NULL;	
	free(*ll);
}
