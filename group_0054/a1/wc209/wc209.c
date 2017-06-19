#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>


int countlines(char *filename);
int countwords(char *filename);
int countchars(char *filename);
int * stdcount(FILE *fp);
int isspace(int c);
int main(int argc, char *argv[]){
    int opt;
    int i = 0;  
    int check = 0;
    int lflag = 0;
    int wflag = 0;
    int cflag = 0;
    

    while ((opt = getopt(argc, argv, "lwc")) != -1) {
      switch (opt) {
               case 'l':
                  lflag = 1;
                  check = 1;
                  break;
               case 'w':
                  wflag = 1;
                  check = 1;
                  break;
               case 'c':
                  cflag = 1;
                  check = 1;
                  break;
               default:
                    check = 2;
                    printf("Error\n");
               }
        }
        if(check == 2){
          lflag = 0;
          wflag = 0;
          cflag = 0;
        }
        else if(!lflag && !wflag && !cflag && !check){
          lflag = 1;
          wflag = 1;
          cflag = 1;
        }
        
        // print for echo
        if(argv[optind] == NULL){
            int *count;
            count = stdcount(stdin);
            int slines = *count;
            int swords = *(count+1);
            int schars = *(count+2);
            if(lflag){
              printf("       %d",slines); 
            } 
            if(wflag){
              printf("       %d",swords); 
            }
            if(cflag){
              printf("      %d",schars); 
            }
            printf("\n");  
        }
        // print individually
        if(check !=2){
            int lines = 0;
            int words = 0;
            int chars = 0;
           for(i = optind; i < argc; i++){
              if(lflag){
                printf("       %d",countlines(argv[i]));
                lines = lines +  countlines(argv[i]);
              } 
              if(wflag){
                printf("       %d",countwords(argv[i])); 
                words = words + countwords(argv[i]);
              }
              if(cflag){
                printf("      %d",countchars(argv[i])); 
                chars = chars + countchars(argv[i]);
              }
              printf(" %s\n", argv[i]); 
            }
            // print total
            if(argc - optind >= 2){
              if(lflag){
                printf("      %d",lines);
              } 
              if(wflag){
                printf("      %d",words); 
              }
              if(cflag){
                printf("      %d",chars); 
              }
              printf(" total\n"); 
          }
        }
       
        

        return 0;
    }

int countlines(char *filename){
  
  FILE *fp = fopen(filename,"r");
  int ch=0;
  int lines=0;

  if (fp == NULL){
       return 0;
  }
 
   while(!feof(fp))
  {
    ch = fgetc(fp);
    if(ch == '\n')
    {
      lines++;
    }
  }
  fclose(fp);
  return lines;
}

int countwords(char *filename)
{
   FILE *fp = fopen(filename,"r");
   int word=0;
   int update_counter = 0;
    for ( ;; )
    {
       int ch = fgetc(fp);
       if (ch == EOF )
       {
          
          if(update_counter){
            word++;
            break;
          }
          else{
            break;
          }
       }
       if (!isspace(ch))
       {
          update_counter = 1;
 
       }
       if (isspace(ch) && update_counter )
       {
          word++;
          update_counter = 0;
       }
    }
   fclose(fp);
   return word;
}

int countchars(char *filename){

   FILE *fp = fopen(filename,"r");
   char ch;
   int chars=0;

   if (fp == NULL){
       return 0;
    }
   while((ch=getc(fp))!=EOF)
   {
        chars++;
   }
   fclose(fp);
   return chars;
}

int * stdcount(FILE *fp){
   int *count = calloc(4, sizeof(int));
   int lines = 0;
   int words = 0;
   int chars = 0;
   int update_counter = 0;
   for(;;){
      int ch = fgetc(fp);
      if (ch != EOF ){
        chars++;
      }
      if(ch == '\n')
      {
        lines++;
      }
      if (ch == EOF )
       {
          
          if(update_counter){
            words++;
            break;
          }
          else{
            break;
          }
      }
       if (!isspace(ch))
       {
          update_counter = 1;
 
       }
       if (isspace(ch) && update_counter )
       {
          words++;
          update_counter = 0;
       }
   } 
   count[0] = lines;
   count[1] = words;
   count[2] = chars;
   return count;
}
