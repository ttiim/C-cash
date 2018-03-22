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
   bcPrint(bc);     //test print function throughout tail function works throughout 
   
   
   // Test 2: Simple Append (one block) -> need to change 
   for (i=0; i<5; i++) {
      ilistAppend(&list, i*11);
   }
   printf("2");
   failed_test_counter += run_test(ilistLen(list), 5, "List length incorrect after Appending 5 items.");
   printf(".");
   failed_test_counter += run_test(ilistGet(list, 4), 44, "List tail Item does not match last item Appended.");
   printf(".");
   
   
   
   
   
   // Test 3: bc isvalid 
   
    
   // Test 5: Destructor
   // Test 5: Destructor (white-box tests)
   printf("5");
   bcDelete(&bc);
   failed_test_counter += run_test(bcLen(bc), 0, "Destructor fails to empty the list.");
   printf(".");
   




   bcDelete(&bc);
   bcPrint(bc);
   printf("\n");


 printf("\n\nUnit Test Suite Complete: ");
 if (failed_test_counter == 0) printf("ALL TESTS PASSED\n");
 else printf("FAILED %d TESTS\n", failed_test_counter);   
}
   
   
   