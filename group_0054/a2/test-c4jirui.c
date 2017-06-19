/**
 * Interesting Test for 209 Heap
 * =======================
 *  Test1
 *  Test first Allocate 5 chunks of memeory, Then treat the pointer point to 
 *  the beginnig of the heap as a char*, and print out the value in it.
 *  Then free the 5 chunks, and print out the value of that pointer agian, see if it 
 *  contians the samething as before. In the end clean up all chunks, and print out that pointer agian.
 *  Test2
 *  Try to use out all memeory in the heap. Then free and allocted in different order, check the result
 *  see if it satisfies the increaing order
 *  The interesting part of test is see how memeory works indeed. 
 */

#include <stdio.h>
#include <string.h>

#include "heap209.h"
#include "diagnostics.h"

// By default our heap will be sized to 128 KiB
#define DEFAULT_HEAP_SIZE (128 * 1024)

/**
 * Helper function to display every heap diagnostic.
 */
static void show_all()
{
    printf("Allocated Chunks:\n");
    show_allocated();
    printf("\n");

    printf("Free Chunks:\n");
    show_free();
    printf("\n");

    printf("All Allocated Memory:\n");
    hexdump_heap();
    printf("\n");
}
void test1(){
    // Initialize the heap with the default size
    heap209_init(DEFAULT_HEAP_SIZE);

    // Allocate 5 chunks of memory
    const int num_chunks = 5;
    void *ptrs[num_chunks];
    size_t num_bytes;
    int i;
    for (i = 0; i < num_chunks; i++) {
        num_bytes = (i + 1) * 4;
        ptrs[i] = malloc209(num_bytes);
        if (!ptrs[i]) {
            printf("ERROR: Failed to allocate %zu bytes, aborting\n", num_bytes);
        }

        // Set each byte in the chunk to an ASCII character.
        unsigned char val = 'A' + i;
        memset(ptrs[i], val, num_bytes);
    }

    /*****part1******/  
    // Show the heap after the allocations
    show_all();
    printf("\n");
    // show the vaule contained in the frist pointer
    printf("vaule in the first pointer:\n%s \n",(char *)ptrs[0]);

    /*****part2******/
    // Free last piece of allocated memory and show again
    int rc = free209(ptrs[4]);
    printf("Releasing %p with `free209` (rc=%d)\n", ptrs[4], rc);
    printf("\n");
    // show the vaule contained in the frist pointer
    printf("vaule in the first pointer:\n%s\n",(char *)ptrs[0]);  
    show_all();
    printf("\n");
    
    /*****part3******/
    //allocate the last piece agian without setting any vaule 
    num_bytes = 20;
    ptrs[4] = malloc209(num_bytes);
    // free the first one
    rc = free209(ptrs[0]);
    printf("Releasing %p with `free209` (rc=%d)\n", ptrs[0], rc);
    printf("\n");
    // show the vaule contained in the frist pointer
    printf("vaule in the first pointer:\n%s\n",(char *)ptrs[0]); 
    printf("\n");
    show_all();

    /*****part4******/
    //allocate the first piece agian without setting any vaule 
    num_bytes = 4;
    ptrs[0] = malloc209(num_bytes);
    // show the vaule contained in the frist pointer
    printf("vaule in the first pointer:\n%s\n",(char *)ptrs[0]);   
    show_all();

    /*****part5******/
    // free all chunks 
    for (i = 0; i < num_chunks; i++) {
         rc = free209(ptrs[i]);
         printf("Releasing %p with `free209` (rc=%d)\n", ptrs[0], rc);
         printf("vaule in the first pointer:\n%s\n",(char *)ptrs[0]);  
         printf("\n");
    }

    show_all();


    /*****part6******/
    // We are done now so let's cleanup after ourselves
    printf("free the heap\n");
    heap209_cleanup();
    printf("vaule in the first pointer:\n%s\n",(char *)ptrs[0]);   

}
void test2(){
    // Initialize the heap with the default size
    heap209_init(200);

    // Allocate 5 chunks of memory
    const int num_chunks = 10;
    void *ptrs[20];
    size_t num_bytes = 20;
    int i;
    for (i = 0; i < num_chunks; i++) {
        ptrs[i] = malloc209(num_bytes);
        if (!ptrs[i]) {
            printf("ERROR: Failed to allocate %zu bytes, aborting\n", num_bytes);
        }

        // Set each byte in the chunk to an ASCII character.
        unsigned char val = 'A' + i;
        memset(ptrs[i], val, num_bytes);
    }
    /*****part1******/  
    // Show the heap after the allocations
    show_all();
    printf("\n");

    /*****part2******/
    // Free last piece of allocated memory and show again
    int rc = free209(ptrs[9]);
    printf("Releasing %p with `free209` (rc=%d)\n", ptrs[4], rc);
    show_all();
    printf("\n");

    /*****part3******/
    // Free first piece of allocated memory and show again
    rc = free209(ptrs[0]);
    printf("Releasing %p with `free209` (rc=%d)\n", ptrs[4], rc);
    show_all();
    printf("\n");

    /*****part4******/
    // Free last second piece of allocated memory and show again
    rc = free209(ptrs[8]);
    printf("Releasing %p with `free209` (rc=%d)\n", ptrs[4], rc);
    show_all();
    printf("\n");

    /*****part5******/
    // Free last second piece of allocated memory and show again
    rc = free209(ptrs[1]);
    printf("Releasing %p with `free209` (rc=%d)\n", ptrs[4], rc);
    show_all();
    printf("\n");

    /*****part6******/
    // Free middle piece of allocated memory and show again
    rc = free209(ptrs[5]);
    printf("Releasing %p with `free209` (rc=%d)\n", ptrs[5], rc);
    show_all();
    printf("\n");

    /*****part7******/
    // allocte all the piece back
    ptrs[0] = malloc209(num_bytes);
    ptrs[1] = malloc209(num_bytes);
    ptrs[5] = malloc209(num_bytes);
    ptrs[8] = malloc209(num_bytes);
    ptrs[9] = malloc209(num_bytes);
    show_all();
    printf("\n");

    /*****part8******/
    // free all the pieces, backword
    for (i = 9; i > -1; i--) {
        rc = free209(ptrs[i]);
        printf("Releasing %p with `free209` (rc=%d)\n", ptrs[i], rc);
        show_all();
        printf("\n");
    }
    /*****part9******/
    // allocte all the pieces,

    for (i = 0; i < 15; i++) {
        ptrs[i] = malloc209(10);
        if (!ptrs[i]) {
            printf("ERROR: Failed to allocate %zu bytes, aborting\n", num_bytes);
        }

        // Set each byte in the chunk to an ASCII character.
        unsigned char val = 'A' + i;
        memset(ptrs[i], val, num_bytes);

    }
     show_all();
    printf("\n");
    /*****part10******/
    // free all the pieces
    for (i = 0; i < 15; i++) {
        rc = free209(ptrs[i]);
        printf("Releasing %p with `free209` (rc=%d)\n", ptrs[i], rc);
        show_all();
        printf("\n");
    }
    heap209_cleanup();
}
int main(int argc, char *argv[])
{
    test1();
    //test2();
    return 0;
}