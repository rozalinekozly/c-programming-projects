/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : Itay
worksheet : 15 (ds - slist exercise)
version   : 1
date      : 15 Dec 2025
stage     : intial
----------------------------------------------------------------------------*/
#include <stdio.h>						/* printf() */
#include <stdlib.h> 						/* malloc(), free() */
#include "../include/slist_ex.h"

/* testing functions */
static void TestFlip();
/* aux functions operations on list */
static void printList(node_ty*); 
static void push(node_ty**, int);



int main() 
{

	TestFlip();
    	return 0;
}

static void TestFlip()
{
  node_ty* head = NULL;
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    printf("Original list: ");
    printList(head);


    head = Flip(head);

    printf("Reversed list: ");
    printList(head);





}
static void printList(node_ty* head) 
{
    node_ty* temp = head;
    while (temp != NULL) {
        printf("%d -> ",*(int*) temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}


static void push(node_ty** head_ref, int new_data)
 {
    node_ty* new_node = (struct Node*)malloc(sizeof(node_ty);
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}





