    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    //function declarations
    int valid_chars_count (char *input, int size);
    int valid_char (char c);
    int check_CpG(char* pos);
    int main (int argc, char *argv[]) {
        char * inputfile_name=argv[1]; 
        FILE * input_fp;
        char *input_buffer; //stores all bytes in the input file
        char *sequence; //char array holding the final cleaned DNA sequence
        
        int *valid_cpg_positions; //array of all positions in sequence
        int input_len, seq_len;
        
        int i, j;
        int r;

        int num_island = 0; //store number of CpG island
        int k;
        int current_index; // store the current index of the array working on
        char *current_start; // store the current pointer of the array working on
        int is_island_part; 
        int *cpg_start;
        int rest_len;
        //int island_start_index;
        //int island_end_index;
        //int island_size;

        FILE * output_fp;
        output_fp = fopen("cpg_output.txt", "w");


        //open the file
        if ( !(input_fp= fopen ( inputfile_name , "rb" )) ) {
            printf("Could not open file \"%s\" for reading input lines \n", inputfile_name);
            return (-1);
        }
        
        //compute total number of characters in the input file
        fseek (input_fp, 0, SEEK_END);
        input_len=ftell (input_fp);
        rewind (input_fp); 
        printf ("total bytes in file: %d\n", input_len);
        
        //allocate an array to hold these characters
        input_buffer = (char*) malloc (input_len+1);
        
        //read file content into the input buffer
        r = fread (input_buffer, 1, input_len,  input_fp);
        printf ("read characters %d\n", r);
        if (r != input_len) {
            printf("Reading error \n");
            return (-1);
        }
        //add terminating character
        input_buffer [input_len] ='\0';

        //determine total number of valid DNA characters
        //and allocate array of chars to hold them
        seq_len = valid_chars_count (input_buffer, input_len);
        printf ("total characters %d total valid characters %d \n", input_len, seq_len);
        sequence = (char*) malloc (seq_len+1); 
        
        //transfer valid characters from raw buffer
        for (i=0, j=0; i < input_len; i++) {
            if (valid_char (input_buffer [i])) {
                sequence [j++] = input_buffer [i];
            }
        }
        sequence [seq_len] = '\0';
        
        //allocate int array for all the positions
        valid_cpg_positions = (int*) malloc (seq_len*sizeof(int));
        for (i=0; i<seq_len; i++)
            valid_cpg_positions[i] = 0;
        i = 0;    
        /* YOUR CpG ISLANDS DISCOVERY CODE HERE */
      
        int reset, start, end, len, numislands=0;
        while(i < (seq_len-199)){
            if(check_CpG(sequence)){
                for(reset=0; reset<200; reset++){
                    if( valid_cpg_positions[i+reset] == 0){
                        valid_cpg_positions[i+reset] = 1;   
                    }
                }
            }
            sequence++;
            i++;
            if(i % 1000000 == 0){
                printf("%d\n", i);
            }
        }  
        
        for (i=0; i<seq_len;){
            if(valid_cpg_positions[i]){
                start = i;
                while(i<seq_len && valid_cpg_positions[i+1]){
                    i++;
                }
                end = i;
                len = end - start + 1;
                numislands++;
                //printf("CpG island      %d..%d      size=%d\n", start,end,len);
            }
            i++;
            if(i % 1000000 == 0){
                printf("%d\n", i);
            }
        }   
        printf("numislands      %d\n", numislands);
        return 0;
    }

    int valid_chars_count (char *input, int size) {
        int i, count = 0;
        for (i=0; i<size; i++) {
            if (valid_char (input [i]) )
                count++;
        }
        return count;
    }

    int valid_char (char c) {
        if (c == 'a' || c == 'c' || c == 'g' || c == 't' ) 
            return 1;
        return 0;
    }

    int check_CpG(char* cur){
        int i, window_size = 200;
        double numC=0.0, numG=0.0, numCG=0.0;
        
        
        for(i=0; i < window_size; i++){
            if(cur[i] == 'g'){
                numG++;
            }
            if(cur[i] == 'c'){
                numC++;
                if(i != (window_size - 1) && cur[i+1] == 'g'){
                    numCG++;
                }
            }
        }

        if(numCG){
            if((numC + numG) > 100){
               if((numCG * 200.0 / numC / numG) >= 0.6) {            
                    return 1;
               }
            }
        }

  
        return 0;   
    }