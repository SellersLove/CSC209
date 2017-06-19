#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mkdir(const char *path, mode_t mode);
long int strtol (const char* str, char** endptr, int base);


/* Returns true if this is end if file*/
int zero_record(const char *p)
{
	int n;
	for (n = 0; n < 512; n++)
		if (p[n] != '\0')
			return 0;
	return 1;
}

/*recursivly create the dir*/
void create_dir(char *path)
{
	char *curr;
	int result;

	if (path[strlen(path) - 1] == '/')
		path[strlen(path) - 1] = '\0';

	result = mkdir(path, 0777);

	if (result != 0) {
		curr = strrchr(path, '/');
		if (curr != NULL) {
			*curr = '\0';
			create_dir(path);
			*curr = '/';
			result = mkdir(path, 0777);
		}
	}
}

/* Create a file, and its parent directory*/
FILE * create_file(char *path)
{
	FILE *f;
	f = fopen(path, "w+");
	if (f == NULL) {
		/* Try creating parent dir and then creating file. */
		char *p = strrchr(path, '/');
		if (p != NULL) {
			*p = '\0';
			create_dir(path);
			*p = '/';
			f = fopen(path, "w+");
		}
	}
	return (f);
}

/* Extract a tar archive. */
void untar(FILE *tar, const char *path)
{
	char buff[512];
	char *ptr;
	FILE *f = NULL;
	size_t bytes_read;
	int filesize;


	for (;;) {
		bytes_read = fread(buff, 1, 512, tar);
		if(feof(tar)){
			break;
		}
		if (bytes_read < 512) {
			break;
		}
		if (zero_record(buff)) {
			break;
		}
		filesize =  (int) strtol(buff + 124, &ptr, 8);
		f = create_file(buff);
		while (filesize > 0) {
			bytes_read = fread(buff, 1, 512, tar);
			if (filesize < 512){
				bytes_read = filesize;
				}
			if (f != NULL) {
				fwrite(buff, 1, bytes_read, f);
			}
			filesize -= bytes_read;
		}
		if (f != NULL) {
			fclose(f);
			f = NULL;
		}
	}
}
int main(int argc, char *argv[])
{	
	FILE *tar;
	argv++;
	tar = fopen(*argv, "r");
	if (tar == NULL)
			printf("Unable to open %s\n", *argv);
		else {
			untar(tar, *argv);
			fclose(tar);
		}
	return 0;
}