
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Create a typedef for easier casting
typedef int (*qsort_comparison)(const void *, const void *);

// `qsort` will pass the comparison function a pointer to something, and in our
// case that something is itself a `char *`, hence we will be receiving `char
// **` as arguments
int my_strcmp(const char **s1, const char **s2)
{
    int rc;

    rc = strcmp(*s1, *s2);

    printf("strcmp(\"%s\", \"%s\") = %d\n", *s1, *s2, rc);

    return rc;
}

int main(int argc, char **argv)
{
    //char a[4][4] = {"ccc","bbb","aaa", "ada"};
    int a[4] = {4,3,2,1};
    // Perform a sort on `argv` (offset by 1 to avoid `argv[0]`)
    qsort((void *) &(a[0]), 4, (size_t) 4, (qsort_comparison) strcmp);
    printf("%d\n",strcmp((char*)&(a[0]),(char*)&(a[1])));
    int i;
    for (i = 0; i < 4; i++) {
        printf("[%d] = \"%d\"\n", i, a[i]);
    }

    return 0;
}
