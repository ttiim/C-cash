/*Capilano University
*   Comp 220- Professor Jospeph Fall
*   Authour: Tim Wriglesworth
*   Worked in collaboration with  Karan Nedungadi
*   Date:15.03.18
    Assignment  Blockchain C-cash  
*  Objectives:Input: any text
    • to implement a doubly-linked list data structure;
    • to deepen our understanding of data structures and dynamic memory; 
	• to learn some basic cryptographic concepts using hash algorithms; 
	• to build a simple blockchain implementation;
  */
  
  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#include "trnslist.h"
#include "puzzle.h"
#include "block.h"
#include "blockchain.h"

/***********************
 * BLOCKCHAIN private implementation details
 ***********************/
const int DEFAULT_DIFFICULTY = 2;              // Default difficulty for hashing puzzles, increase to make mining harder

//helper prototypes
void bcpop(bc_t* bc);
bool bcIsEmpty(bc_t bc);
void blockPrint(const Block_t blk) ;

/***************************************
 * Helper functions
 * **************************************/


void bcpop(bc_t* bc)   //mutable function // Dynamic transactions in t are owned by this Block and will be deleted when this Block is deleted!
{
    
   assert(!bcIsEmpty(*bc));   
   Block_t* blk = bc->head->next;
   bc->head->next=blk->next;
   
   if (bc->tail == blk) 
   {
	   bc->tail = bc->head;
	   }
	   
    blkDelete(blk); 

}


bool bcIsEmpty(const bc_t bc) 
{
   return bc.head->next == NULL;
}


void blockPrint( Block_t blk)    //could print the other elements of the block but will only do if we distribute it-then we can look up.
{
    printf("____________________________________________________\n");
    static int i=0;
    printf("Block [%d]\n", i);
    
   // printf("------------------------------------\n");
    TransactionList list= blk.transactions;
    tlistPrint(list);
   // printf("------------------------------------\n");
    
    i++;

  printf("id: [%d]%s\n", blk.id-1, blk.next ? "-->" : "\n|____________________________________________________|");
   
  printf( "This Block's Hash is:");
  printHash(blk.hash);
    
    
    
}


 



/***************************************
 *Blockchain Implementation 
 * **************************************/

/*
 * Constructor - return a new, empty bc_t 
 * POST:  bcLen(chain) == 0
 */
bc_t bcNew( )
{
  TransactionList t1 = tlistCreate(); // only would create a bc when needing a transaction list.
  Block_t* zeroBlock = blkCreate(t1, DEFAULT_DIFFICULTY, NULL_NONCE);  //dummy nodey
  bc_t bc = {zeroBlock, zeroBlock};
  blkComputeHash(zeroBlock);  ///needs random hash
  return bc;
  
}


/*
 * Destructor - remove all data and free all memory associated with the chain 
 * POST: bcLen(chain) == 0
 */
void bcDelete( bc_t *chain)
{
    
    while (chain->head->next != NULL) 
	 {
		 bcpop(chain);
		
		 }
}

/*
 * Print a text representation of this chain on STDOUT
 */
void bcPrint( const bc_t chain )
{
  
  Block_t* cur = chain.head; 
  printf("\nBlockchain:\n  ");
  
  
  while (cur != NULL) 
  {
	  blockPrint(*cur);
      cur = cur->next;
	  }
	  
	  printf("\n\n");	
}

/*
 * Return the number of Blocks in the chain
 */
int bcLen( const bc_t chain )
{
  Block_t* cur = chain.head->next;
  int len = 0;
  while (cur != NULL) 
  {
	  len++;
	  cur = cur->next;
	  }
	  
	  return len;
    
}

/*
 *  Return true iff blkIsValid(block) for every block in the chain
 */
bool bcIsValid(const bc_t chain)
{
    
  Block_t* cur = chain.head->next;
  
  while (cur != NULL) 
  {
	  if (!blkIsValid(*cur))     // bool blkIsValid(const Block_t block);
	  {
	      return false;
	      
	  }
	  
	  cur = cur->next;
      
  }
    
   return true;
}


/*
 * Return a pointer to the chain's tail Block
 */
Block_t* bcTail(const bc_t chain)
{
    return chain.tail;
}

/*
 * Append the given block to the chain 
 *    iff blkValidates(new_block, bcTail->hash, new_block->proof_of_work)
 * POST: bcTail(*chain) == new_block && blkIsValid(*new_block)
 */
void bcAppend( bc_t *chain, Block_t* new_block )
{
    if (bcIsEmpty(*chain))
    {
        
        chain->head->next = chain->tail= new_block;
        new_block->prev = chain->head;
        blkComputeHash(new_block);                      ///----
    }
    else
    {
     blkChainTo(chain->tail, new_block);
     chain->tail= new_block;
    }
   
    
   // printf("prev hash:");
    //printHash(new_block->prev->hash);                         ///---
   
//   //printf("chain->tail");
//   //blockPrint(*bcTail(*chain));
//   printf("The value of the boolean expression [blkisValid is]: \n");
//   printf("%d\n\n\n", blkIsValid(*new_block));
   
//   printf("the new block is:\n" );
//   blockPrint(*new_block);
//     printf("prev hash:\n\n\n");
   //printHash(new_block->prev->hash);
   
   
  // printf("appending block....");
   
   
   
   
    assert (bcTail(*chain) == new_block && blkIsValid(*new_block));   
   
}
  
  
  
  
  
  
  
