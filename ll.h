#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// self-referential structure
struct Node {
    int id;               // user ID
    char name[50];        // user Name
    struct Node *nextPtr; // pointer to next node
    struct Node *pPtr;    // pointer to previous node (Doubly Linked List)
}; // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr;      // synonym for ListNode

// prototypes
int deletes( LLPtr *sPtr, int id );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int id, char name[] );
void printList( LLPtr currentPtr );
void PrintlistR( LLPtr currentPtr ); // เพิ่ม prototype สำหรับปริ้นท์ย้อนกลับ
void instructions( void );
void clearList( LLPtr *sPtr ); // Added for clearing nodes on exit

// display program instructions to user
void instructions( void )
{
    puts( "Enter your choice:\n"
       "   1 to insert an element into the list.\n"
       "   2 to delete an element from the list.\n"
       "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order by ID
void insert( LLPtr *sPtr, int id, char name[] )
{
    LLPtr newPtr; // pointer to new node
    LLPtr previousPtr; // pointer to previous node in list
    LLPtr currentPtr; // pointer to current node in list

    newPtr = (LLPtr) malloc( sizeof( LLnode ) ); // create node

    if ( newPtr != NULL ) { // is space available
        newPtr->id = id; // place id in node
        strcpy(newPtr->name, name); // place name in node
        newPtr->nextPtr = NULL; // node does not link to another node
        newPtr->pPtr = NULL;    // initialize previous pointer
        
        previousPtr = NULL;
        currentPtr = *sPtr;

        // loop to find the correct location in the list (Sorted by ID)
        while ( currentPtr != NULL && id > currentPtr->id ) {
            previousPtr = currentPtr; // walk to ...
            currentPtr = currentPtr->nextPtr; // ... next node
        } // end while

        // insert new node at beginning of list
        if ( previousPtr == NULL ) {
            newPtr->nextPtr = *sPtr;
            
            if ( *sPtr != NULL ) {
                (*sPtr)->pPtr = newPtr; // Update old head's previous pointer
            }
            
            *sPtr = newPtr;
        } // end if
        else { // insert new node between previousPtr and currentPtr
            previousPtr->nextPtr = newPtr;
            newPtr->pPtr = previousPtr; // Update previous pointer to point backward
            
            newPtr->nextPtr = currentPtr;
            
            if ( currentPtr != NULL ) {
                currentPtr->pPtr = newPtr; // Update next node's previous pointer to point to new node
            }
        } // end else
    } // end if
    else {
        printf( "%d not inserted. No memory available.\n", id );
    } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr, int id )
{
    LLPtr previousPtr; // pointer to previous node in list
    LLPtr currentPtr; // pointer to current node in list
    LLPtr tempPtr; // temporary node pointer

    if ( isEmpty( *sPtr ) ) return '\0';

    // delete first node
    if ( id == ( *sPtr )->id ) {
        tempPtr = *sPtr; // hold onto node being removed
        *sPtr = ( *sPtr )->nextPtr; // de-thread the node
        
        if ( *sPtr != NULL ) {
            (*sPtr)->pPtr = NULL; // Update new head's previous pointer
        }
        
        free( tempPtr ); // free the de-threaded node
        return id;
    } // end if
    else {
        previousPtr = *sPtr;
        currentPtr = ( *sPtr )->nextPtr;

        // loop to find the correct location in the list
        while ( currentPtr != NULL && currentPtr->id != id ) {
            previousPtr = currentPtr; // walk to ...
            currentPtr = currentPtr->nextPtr; // ... next node
        } // end while

        // delete node at currentPtr
        if ( currentPtr != NULL ) {
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            
            if ( currentPtr->nextPtr != NULL ) {
                currentPtr->nextPtr->pPtr = previousPtr; // Bypass deleted node for backward link
            }
            
            free( tempPtr );
            return id;
        } // end if
    } // end else

    return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{
    return sPtr == NULL;
} // end function isEmpty

// print the list (Forward Traversal Only)
void printList( LLPtr currentPtr )
{
    // if list is empty
    if ( isEmpty( currentPtr ) ) {
        puts( "List is empty.\n" );
    } // end if
    else {
        puts( "The list is:" );

        LLPtr tempPtr = currentPtr;

        // ขาไป (Forward Traversal)
        while ( tempPtr != NULL ) {
            printf( "%d %s --> ", tempPtr->id, tempPtr->name );
            tempPtr = tempPtr->nextPtr;
        } // end while
        puts( "NULL" );
    } // end else
} // end function printList

// print the list backward (Backward Traversal)
// print the list backward (Backward Traversal)
void PrintlistR( LLPtr currentPtr )
{
    // if list is empty
    if ( isEmpty( currentPtr ) ) {
        puts( "List is empty.\n" );
    } // end if
    else {
        //puts( "The reversed list is:" ); // ปรับข้อความนำให้เข้ากับการปริ้นท์ย้อนกลับ

        LLPtr tempPtr = currentPtr;

        // find last node
        while ( tempPtr->nextPtr != NULL ) {
            tempPtr = tempPtr->nextPtr;
        } // end while

        // ขากลับ (Backward Traversal)
        while ( tempPtr != NULL ) {
            printf( "%d %s --> ", tempPtr->id, tempPtr->name );
            tempPtr = tempPtr->pPtr; // use pPtr
        } // end while
        puts( "NULL" );
    } // end else
} // end function PrintlistR

// Clear all nodes when exiting (Choice 3)
void clearList( LLPtr *sPtr )
{
    if ( !isEmpty( *sPtr ) ) {
        puts( "Clear all nodes" );
        LLPtr tempPtr;
        
        while ( *sPtr != NULL ) {
            tempPtr = *sPtr;
            printf( "delete %d\n", tempPtr->id );
            *sPtr = ( *sPtr )->nextPtr;
            free( tempPtr );
        }
    }
} // end function clearList