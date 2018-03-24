/*  Capilano University
*   Comp 220- Professor Jospeph Fall
*   Authour: Tim Wriglesworth
*   Worked in collaboration with  Karan Nedungadi
*   Date:15.03.18
*    Assignment  Blockchain C-cash  
*    
*   Develop a test driver! 
*   • It does not have to be fancy – it could be interactive or automated or a mixture of both 
*   (like the linked list test driver from labs 5 & 6). 
*   • Write some tests for every function you develop so that you can verify and debug each function independently.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "trnslist.h"
#include "puzzle.h"
#include "block.h"
#include "blockchain.h"

const int DEFAULT_DIFFICULTYY = 2;
/*
* Run a single test case
* Report on failed test
* Return 0 if test successful, 1 otherwise
*/

int run_test(int result, int expected, char* msg) 
{

   if (result != expected)
   {
      printf("\nTest failed: %s \n\tFunction returned %d but expected %d\n", msg, result, expected);
      return(1);
   }
   return(0);
}

/*
 * Run a series of unit tests cases.
 * Report on failed tests.
 */
void main()
{
   int i;
   int failed_test_counter = 0;
   printf("Unit Test Suite for IntList ADT operations...\n");
   
   // Test 1: Constructor
   bc_t bc = bcNew();
   printf("1");
   failed_test_counter += run_test(bcLen(bc), 0, "Constructor fails to create empty list.");
   printf(".");
   
   //bcPrint(bc);     
    //printf("the lenght of the Blockchain is [%d]\n", bcLen(bc));
   
   
   
   // Test 2: Simple Append (one block) 
   TransactionList t1 = tlistCreate( );                     //need to create a transaction list
   for (i=0; i<5; i++) 
   {
      tlistAppend(&t1, "Tim", 12.34, "Cici");
   }
   
   Block_t* newBlk = blkCreate(t1 , DEFAULT_DIFFICULTYY, NULL_NONCE);        
   
   //bcPrint(bc);
   Puzzle_t newPuzzle = blkCreatePuzzle(*newBlk, bc.tail->hash);
   newBlk->proof_of_work = puzzleMine(newPuzzle);
   
   
   //bcPrint(bc);
   
   
    printf("2");
    bcAppend(&bc,newBlk);
    failed_test_counter += run_test(bcLen(bc), 1, "List length incorrect after Appending 1 items.");
    printf(".");
   
   
    
  
  //Test 3: append a second block
 
  TransactionList t2 = tlistCreate( );                     //need to create a transaction list
   for (i=0; i<5; i++) 
   {
      tlistAppend(&t2, "Tom", 12.34, "Sarah");
   }
   
   Block_t* newBlk2 = blkCreate(t2 , DEFAULT_DIFFICULTYY, NULL_NONCE);        
   //bcPrint(bc);
   
   char buffer2 [tlistSerialLen(t2)+1];               // serialize the data to work with (for practice)
   buffer2[0]= '\0';
   tlistSerialize(newBlk2->id, t2, buffer2);
   
   
   Puzzle_t newPuzzle2 = puzzleCreate(buffer2, bc.tail->hash, DEFAULT_DIFFICULTYY );          //create puzzle to find a valid proof of work
   
   newBlk2->proof_of_work = puzzleMine(newPuzzle2);
   
  
  //bcPrint(bc); 
  
   
   
   // printf("The Second Append: \n\n");
   printf("3");
   bcAppend(&bc,newBlk2);
   failed_test_counter += run_test(bcLen(bc), 2, "List length incorrect after Appending 1 items.");
   printf(".");
   
   //-------------------------------------------------------------------------///
   
   
   TransactionList t3 = tlistCreate( );                     //need to create a transaction list
   for (i=0; i<5; i++) 
   {
      tlistAppend(&t3, "logan", 12.34, "emily");
   }
   
   Block_t* newBlk3 = blkCreate(t3 , DEFAULT_DIFFICULTYY, NULL_NONCE);        
   
   //bcPrint(bc);
   Puzzle_t newPuzzle3 = blkCreatePuzzle(*newBlk3, bc.tail->hash);
   newBlk3->proof_of_work = puzzleMine(newPuzzle3);
   
   
   printf("4");
   bcAppend(&bc,newBlk3);
   failed_test_counter += run_test(bcLen(bc), 3, "List length incorrect after Appending 1 items.");
   printf(".");
   
   
   
   
   
   
   
   
   //Test 5: test if entire chain is valid.
   printf("5");
   failed_test_counter += run_test(bcIsValid(bc), true, "Blockchain is not valid");
   printf(".");
   
   
   //printf("THE BLOCKCHAIN with 3 Blocks of Data\n");
   //bcPrint(bc); 
   
// Test 5: Destructor: destroy the blockchain chain
   
   printf("6");
   bcDelete(&bc);
   failed_test_counter += run_test(bcLen(bc), 0, "Destructor fails to empty the list.");
   printf(".");
   //bcPrint(bc);
   
   



 printf("\n\nUnit Test Suite Complete: Tim You have won ");
 if (failed_test_counter == 0) printf("ALL TESTS PASSED\n");
 else printf("FAILED %d TESTS\n", failed_test_counter);   
 
}
   
   
   