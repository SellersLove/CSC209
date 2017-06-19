
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{	
	unsigned short set =0b1000100010001001;
    int i;
    for(i=0; i < 16; i++) {
        if((set >> i ) & 1)
        	printf("%d\n", i);
     }
    return 0;
}