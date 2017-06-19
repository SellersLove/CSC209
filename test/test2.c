#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
   char *values[4] = { "aba", "bba", "ccc"};


   //char b[] = "adasda";
   char *b = "adasda";
//   b[0] = 'q';
   printf("%p\n", &values[0]);
   printf("%p\n", &values[1]);
   printf("%p\n", &values[2]);
   printf("%p\n", &b[0]);
   printf("%s\n", values[0]);
   printf("%d\n", (int)sizeof(values[0]));
    return 0;
}