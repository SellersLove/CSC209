#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("Running /bin/ls...\n");

    execlp("/bin/ls",
            "ls",
            (char *) NULL);

    perror("execlp");

    return EXIT_FAILURE;
}
