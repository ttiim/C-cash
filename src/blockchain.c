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
  
  /*
  
  Draw out some doubly linked lists and how they look. keep looking through given code. remember dont need to understand every bit to understand what you
  are working on.
  
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
void bcpop(Blockchain* bc);
bool bcIsEmpty(BlockChain bc);

/***************************************
 * Helper functions
 * **************************************/


void bcpop(Blockchain* bc)    // Dynamic transactions in t are owned by this Block and will be deleted when this Block is deleted!
{
    
   assert(!bcIsEmpty(*stack));   
   Block_t* blk = bc->head->next;
   bc->head->next=bc->next;
   
   if (bc->tail == blk) 
   {
	   bc->tail = bc->head;
	   }
	   
    blkDelete(blk); 
    
    
    
    
}


bool bcIsEmpty(const BlockChain bc) 
{
   return bc.head->next == NULL;
}








/***************************************
 *Blockchain Implementation 
 * **************************************/

/*
 * Constructor - return a new, empty BlockChain 
 * POST:  bcLen(chain) == 0
 */
BlockChain bcNew( );
{
  block_t* firstBlk = blkCreate(tlistCreate(),DEFAULT_DIFFICULTY, NULL_NONCE);  //dummy node? that contains all emty items. -block only created when listdata
  BlockChain bc = {firstBlk, firstBlk}
}


/*
 * Destructor - remove all data and free all memory associated with the chain 
 * POST: bcLen(chain) == 0
 */
void bcDelete( BlockChain *chain)
{
    
    while (chain->head->next != NULL) 
	 {
		 llPop(chain);
		 }
}

/*
 * Print a text representation of this chain on STDOUT
 */
void bcPrint( const BlockChain chain ); 

/*
 * Return the number of Blocks in the chain
 */
int bcLen( const BlockChain chain )
{
  block_t* cur = chain.head->next;
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
bool bcIsValid(const BlockChain chain)
{
    
  Block_t* cur = chain.head->next;
  
  while (cur != NULL) 
  {
	  if (!blkIsValid(chain))
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
Block_t* bcTail(const BlockChain chain)
{
    return chain.tail;
}

/*
 * Append the given block to the chain 
 *    iff blkValidates(new_block, bcTail->hash, new_block->proof_of_work)
 * POST: bcTail(*chain) == new_block && blkIsValid(*new_block)
 */
void bcAppend( BlockChain *chain, Block_t* new_block )
{
    block_t*cur = new_block;
    
    blkChainTo(tail_block, new_block);
    chain->tail->next=cur;
    
    assert (bcTail(*chain) == new_block && blkIsValid(*new_block));   
   
}
  
  
  
  
  
  
  
