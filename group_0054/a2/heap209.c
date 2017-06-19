/**
 * heap209.c
 * =========
 * 
 * Implements a small heap space organized into chunks of free and allocated
 * space (maintained through linked lists.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/mman.h>

#include "heap209.h"

void *heap_region = NULL;
Chunk *free_list = NULL;
Chunk *alloc_list = NULL;
/**
 * Precondition: the chunk_list contains chunk
 * A recursive function which removes a chunk from a chunk_list, based on the chunk->addr.
 */
void removeChunk(Chunk** chunk_list, Chunk *chunk){
    // the first element in chunk_list is the chunk that we suppose to remove
    if((*chunk_list)->addr == chunk->addr){
        *chunk_list = (*chunk_list)->next;
        return;
    }
    //recursive call
    else{
        removeChunk(&((*chunk_list)->next), chunk);
        return;
    }
}

/**
 * Precondition: chunk_list is in increasing order.
 * A recursive function which insert a chunk into a chunk_list and satisfies
 * the increasing order, based on the chunk->addr. 
 */
void insertChunk(Chunk **chunk_list, Chunk *chunk){
    // if the chunk_list is NULL, then just let chunk_list equal to chunk.
    if(*chunk_list == NULL){
        *chunk_list = chunk;
        return;
    }
    //the first element in the chunk_list have a bigger address than chunk
    else if((*chunk_list)->addr > chunk->addr){
        chunk->next = *chunk_list;
        (*chunk_list) = chunk;
        return;
    }
    // recursive call which finds out the first element has an address bigger than chunk's
    else{
        insertChunk(&((*chunk_list)->next), chunk);
        return;
    }
}

/**
 * Allocate `nbytes` from the heap, and returns a pointer to the start of the
 * freshly allocated memory. Returns NULL if there is insufficient free
 * contiguous space.
 */
void *malloc209(size_t nbytes){

    Chunk *current = free_list;
    while(current != NULL){
        if(current->size > nbytes){
            // malloc a new chunk and pass it to alloc_list
            Chunk* new = (Chunk*) malloc(sizeof(Chunk)); 
            void *addr= current->addr;
            new->addr = addr;
            new->size = nbytes;
            new->next = NULL;
            insertChunk(&alloc_list, new);
            // change the current chunk to a different address and size
            current->addr += (int)nbytes;
            current->size -= nbytes;
            return addr;
        }
        else if(current->size == nbytes){
            //remove the current from free_list
            removeChunk(&free_list, current);
            current->next = NULL;
            // add it to alloc_list
            insertChunk(&alloc_list, current);
            return current->addr;
        }
        else{
            current = current->next;
        }
    }
    // fail to allocate
    return NULL;
}

/**
 * Release the previously allocated memory pointed to by `addr` back into the
 * heap. Returns 0 on success, or -1 if `addr` was not found in the allocated
 * chunk list.
 */
int free209(void *addr)
{
    Chunk *current = alloc_list;
    while(current != NULL){
        // find the required chunk
        if(current->addr == addr){
            //remove from the alloc_list
            removeChunk(&alloc_list,current);
            current->next = NULL;
            // add to free_list;
            insertChunk(&free_list, current);
            return 0;
        }
        else{
            current = current->next;
        }
    }
    return -1;
}

/**
 * Initialize a large piece of contiguous memory to serve as the heap region.
 *
 * NB: mmap(1) is a system call that is used to create new regions within the
 * virtual (logical) address space of the calling process. It can be used to
 * map the contents of files into memory, so that you can directly access the
 * file data through memory pointers instead of requiring explicit read and
 * write function calls. Here we are using it in a slightly different way in
 * order to negotiate with the operating system to give us a large region of
 * memory for our private use (without any files being involved.)
 *
 * The `mmap` call will return a `void *` pointer to the allocated memory. It's
 * arguments are:
 *
 *  - NULL: let the kernel choose where to place the memory in the address
 *      space.
 *  - PROT_READ | PROT_WRITE: bitmask to indicate memory will be used for
 *      reading and writing
 *  - MAP_PRIVATE | MAP_ANON: create an anonymous mapping that is private (only
 *      visible) to this process
 *  - -1: no file descriptor as this mapping is not backed by a file
 *  - 0: no offest, again because no files are involved
 */
void heap209_init(size_t heap_size)
{
    if (heap_region) {
        fprintf(stderr, "ERROR: Cannot re-initialize the 209 heap\n");
        return;
    }
    heap_region = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

    if (heap_region == MAP_FAILED) {
        perror("mmap");
        exit(-1);
    }
    // initialize free_list
    free_list = (Chunk*) malloc(sizeof(Chunk));
    if(free_list != NULL){
        free_list->addr = heap_region;
        free_list->size = heap_size;
        free_list->next = NULL;
    }
    alloc_list = NULL;
 
}


/**
 * Clean up chunk metadata.
 */
 void chunk_cleanup(Chunk** chunk){
    if((*chunk) != NULL){
        if((*chunk)->next == NULL){
            free(*chunk);
        }
        else{
            chunk_cleanup(&((*chunk)->next));  
            (*chunk)->next = NULL; 
            chunk_cleanup(chunk); 
        }
    }
 }

/**
 * Clean up all chunk metadata associated with the heap.
 */
void heap209_cleanup()
{
    // TODO FIXME: Implement cleanup of all heap metadata
    chunk_cleanup(&alloc_list);
    chunk_cleanup(&free_list);
}
