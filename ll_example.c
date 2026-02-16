// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include "ll.h"

int main( void )
{ 
   LLPtr startPtr = NULL; // initially there are no nodes
   unsigned int choice;   // user's choice
   int id;                // ID entered by user
   char name[50];         // Name entered by user

   instructions(); // display the menu
   printf( "? " );
   scanf( "%u", &choice );

   // loop while user does not choose 3
   while ( choice != 3 ) { 

      switch ( choice ) { 
         case 1:
            // รับค่าทั้ง id และ name
            printf( "Enter id and name: " );
            scanf( "%d %s", &id, name );
            insert( &startPtr, id, name ); // insert id and name in list
            
            printList( startPtr );         
            PrintlistR( startPtr ); //
            break;

         case 2: // delete an element
            // if list is not empty
            if ( !isEmpty( startPtr ) ) { 
               printf( "Enter number to be deleted: " );
               scanf( "%d", &id );

               // if character is found, remove it
               if ( deletes( &startPtr, id ) ) { // remove item
                  printf( "%d deleted.\n", id );
                  printList( startPtr );
                  PrintlistR( startPtr ); 
               } // end if
               else {
                  printf( "%d not found.\n\n", id );
               } // end else
            } // end if
            else {
               puts( "List is empty.\n" );
            } // end else
            break;

         default:
            puts( "Invalid choice.\n" );
            instructions();
            break;
      } // end switch

      printf( "? " );
      scanf( "%u", &choice );
   } // end while

   
   clearList( &startPtr );
   puts( "End of run." );

   
   return 0; 
} // end main