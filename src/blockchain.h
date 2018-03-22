/**
 *  BlockChain ADT : public interface
 *      A doubly-linked chain of Blocks, using cryptographic hash to guarantee immutibility
 *
 *  COMP220: Assignment 3
 *  Author:  Joseph Fall
 *  Date:    Feb. 1, 2018
 */
 
/*******************
 * PRIVATE TYPE DECLARATIONS
 ********************/
typedef struct {
    Block_t* head;
    Block_t* tail;
} bc_t;

/*********************
 *  PUBLIC INTERFACE
 *********************/
 
/*
 * Constructor - return a new, empty BlockChain 
 * POST:  bcLen(chain) == 0
 */
bc_t bcNew( );

/*
 * Destructor - remove all data and free all memory associated with the chain 
 * POST: bcLen(chain) == 0
 */
void bcDelete( bc_t *chain ); 

/*
 * Print a text representation of this chain on STDOUT
 */
void bcPrint( const bc_t chain ); 

/*
 * Return the number of Blocks in the chain
 */
int bcLen( const bc_t chain );

/*
 *  Return true iff blkIsValid(block) for every block in the chain
 */
bool bcIsValid(const bc_t chain);


/*
 * Return a pointer to the chain's tail Block
 */
Block_t* bcTail(const bc_t chain);

/*
 * Append the given block to the chain 
 *    iff blkValidates(new_block, bcTail->hash, new_block->proof_of_work)
 * POST: bcTail(*chain) == new_block && blkIsValid(*new_block)
 */
void bcAppend( bc_t *chain, Block_t* new_block );
