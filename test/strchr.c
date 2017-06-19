#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char ** split_on_comma(char * s) {
    /* This is one approach to solving this problem. It is not the
       only correct answer */
    int comma_index;
    comma_index = strchr(s, ',') - s;
    char ** result = malloc (2 * sizeof(char *));
    result[0] = malloc((comma_index + 1) * sizeof(char));
    //s contains comma_index digits and 1 comma and then the name
    // but we need space for the null-terminator
    result[1] = malloc(strlen(s) - comma_index);
    int i;
    for (i=0; i< comma_index; i++) {
        result[0][i] = s[i];
    }
    result[0][comma_index] = '\0';
    // <= is so that we also copy the null terminator
    for (i=comma_index + 1; i <= strlen(s) ; i++) {
        result[1][i-comma_index - 1] = s[i];
    }
    return result;
}
void free_all(char ** r) {
    free(r[0]);
free(r[1]);
free(r); }
int main() {
    char ** r;
	char * s2 = "Reid,Karen";
    r = split_on_comma(s2);
    printf("first token is %s and second token is %s\n",r[0],r[1]);
    free_all(r);
    // may call free_all here again. Either way is ok.
return 0; }
