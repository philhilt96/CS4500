#include "list.h"
#include <stdio.h>

int main(void) {
    // list creation
    list* testList = create_list();

    // Check if list was created
    if (testList == NULL) {
	printf("%s\n", "List could not be created.");
	return 1;
    }    
    
    // test adding node to list
    printf("%s\n", "Linked List after adding two nodes:");
    add_to_list(testList, "first node");
    add_to_list(testList, "second node");
    print_list(testList); 

    // test removing head from list
    char* itemRemoved = remove_from_list(testList);

    printf("%s %s:\n", "Linked list after removing", itemRemoved);
    print_list(testList); 

    // test flush list
    flush_list(testList);

    // Print empty list and show null head pointer
    printf("%s:\n", "Linked list after flushing");
    print_list(testList);
    printf("%s: %p\t%s: %p\n", "List addr", testList, "Head Node", testList->head);
    
    // test free list    
    add_to_list(testList, "first node");
    add_to_list(testList, "second node"); 
    printf("%s\n", "Linked List after adding two nodes:");
    print_list(testList);

    // Pass a pointer to free list so it can access the memory location of testList    
    printf("%s\n", "Linked List after freeing:");
    free_list(&testList);
    printf("%s%p\n", "Test list address: ", testList); 
    print_list(testList);
	
    return 0;
}
