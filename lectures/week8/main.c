#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char const *argv[]){

int fd = open("out.txt",O_CREAT|O_WRONLY |O_TRUNC, 0666  );
dup2(fd,1);
printf("hello world!\n");
char*argv2[2];
argv2[0] = "ls";
argv2[1] = NULL;
execvp(argv2[0],argv2);
}
