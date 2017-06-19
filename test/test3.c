#include <stdio.h>
#include <string.h>

/**
 * Use `strsep` to tokenize a string.
 *
 * Try:
 *
 *      $ ./strsep ' ' "Hello CSC209 World!"
 *
 *  Or,
 *
 *      $ ./strsep '!@$%*' 'Can!anyone@hear$me%in*here?'
 */
int main(int argc, char *argv[])
{   
    union U {
        struct S {
            short a;
            char b;
            char c;
        } s;
        struct K {
            char a;
            char b;
        } h;

    } x;
    x.s.a = 2;
    x.s.b = 2;
    printf("%d\n", (int)sizeof(x));
    printf("x.s %p\n", &x.s);
    printf("x.s.a %p\n", &x.s.a);
    printf("x.s.b %p\n", &x.s.b);
    printf("x.s.c %p\n", &x.s.c);
    printf("(&x.s.a+ 1): %p\n", (&x.s.a+ 1));
    printf("(&x.s.b + 1): %p\n", (&x.s.b + 1));
    printf("(&x.s.c + 1): %p\n", (&x.s.c + 1));
    printf("(&x.s + 1): %p\n", (&x.s + 1));
    printf("(&x.s ): %p\n", (&x.s ));
    printf("(&x.s.a): %p\n", (&x.s.a));
    printf("(&x.h + 1): %p\n", (&x.h + 1));
    return 0;
}