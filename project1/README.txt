CS4500 Project 1 README

Chace Bauer, Sean Campbell, Phil Hilt
We have neither given nor received unauthorized assistance on this work.

VM:
 cbauer2 > cbauer VM
User: root
PWD: password
Code Directory: /home/cbauer/project1

This project shows a basic implementaion of a linked list in C.

A Makefile is used to organize code compilation by allowing a user to compile
with the make command. THe document at http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ was used as a reference to write the Makefile. The gcc compiler was specified, and -Wall was set as a CFLAG. The target of the Makefile was the executable "list". 

list.h contains the prototypes for functions used and list.c contains function definitions.
test_list.c contains code to test the implementation of the linked list.

The linked list is made of two user defined struct datatypes: 
	- node holds a pointer to a character string item along with a pointer to the next node
        - list holds a pointer to the head node of the linked list

create_list function allocates memory for a new list (if there is memory avaiable) and sets the head to NULL

add_to_list takes in a linked list and a char string as arguments. The function allocates memory for a new node node (if memory is available) with the specified item to append to the specified list.  
The list is traversed by checking for a null pointer, once it is found, that last nodes pointer is set to the new node and the new nodes pointer is set to null.

remove_from_list removes the head of a specified list and returns the char string item of the head node. This function stores the head node in a temp node, before setting the head node to the next node. It then frees memory of the temp node and returns the item associated with that node.

print_list prints all the items of a provided linked list by traversing a list if it is not NULL. If the provided list is NULL it will print a string indicating such

flush_list clears every node in a provided list. A current node is defined to the provided list head and a previous node is set to null. A while loop is used to traverse the list, moving current node to the next node and freeing the memory of previous node. After the loop current is freed and the list head is re-initialized to NULL.

free_list() is used to de-allocate all memory in a linked list. A pointer to a list is used as argument so that the list's head can be freed after memory is deallocated for every node. 




