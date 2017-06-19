#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int opt, num_proc = 0;
	char *infile_dir = NULL;
  	char *outfile = NULL;

  	/* read in arguments */
  	while ((opt = getopt(argc, argv, "f:n:o:")) != -1) {
      	
      	switch(opt) {
            case 'f': infile_dir = optarg;
            	printf("%s\n", infile_dir);
                break;
            case 'n': num_proc = atoi(optarg);
            	printf("%d\n", num_proc);
                break;
            case 'o': outfile = optarg;
                break;
            default : fprintf(stderr, "Usage:  test -f <input file name> "
                              "-o <output file name>\n");
                exit(1);
        }
  	}


}