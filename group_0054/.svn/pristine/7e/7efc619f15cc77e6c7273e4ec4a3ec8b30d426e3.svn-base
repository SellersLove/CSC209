#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "execute.h"
#include "command.h"

static int run_program(Command *cmd);
static int execute_command_with_pipe(Command *cmd);

/** Builtin command handlers */
static int execute_builtin_cd(char *argv[]);
static int execute_builtin_exit(char *argv[]);

/**
 * Execute a Command (with or without pipes.)
 */
int execute_command(Command *cmd)
{
    /* TODO: Remove this once you're done */
    //printf("Command: ");
    //command_dump(cmd);

    // Check for builtin commands
    if (strcmp(cmd->argv[0], "cd") == 0) {
        return execute_builtin_cd(cmd->argv);
    }

    if (strcmp(cmd->argv[0], "exit") == 0) {
        return execute_builtin_exit(cmd->argv);
    }

    if (cmd->pipe_to == NULL) {
        /* TODO: Implement executing a simple command without pipes.
         *
         * Use `fork` to run the function `run_program` in a child process, and
         * wait for the child to terminate.
         */

        // Fork this process in order to create a child
        pid_t child = fork();
         // Fork returns a negative value (-1) if the system call failed
        if (child < 0) {
            perror("fork error");
            return -1;
        }
        if (child == 0) {
            // in child process
            run_program(cmd);
        }
        else {
            // in parent process wait the child to execute
            int status;
            wait(&status);
        }

        return 0;
    }
    else {
        return execute_command_with_pipe(cmd);
    }

    return EXIT_FAILURE;
}

/**
 * `cd` -- change directory (builtin command)
 *
 * Changes directory to a path specified in the `argv` array.
 *
 * Example:
 *      argv[0] = "cd"
 *      argv[1] = "csc209/a3"
 *
 * Your command MUST handle either paths relative to the current working
 * directory, and absolute paths relative to root (/).
 *
 * Example:
 *      relative path:      cd csc209/a3
 *      absolute path:      cd /u/csc209h/summer/
 *
 * Be careful and do not assume that any argument was necessarily passed at all
 * (in which case `argv[1]` would be NULL, because `argv` is a NULL terminated
 * array)
 */
static int execute_builtin_cd(char *argv[])
{
    char *arg = argv[1];

    // check if the argument is a absolute path
    int is_absolute = (arg && arg[0] == '/');
    char *buf;
    size_t size = 100;
    buf = (char *)malloc(size);
    /*
     * TODO: Implement this function using `chdir(2)` and `getcwd(3)`.
     *
     * If the argument is absolute, you can pass it directly to chdir().
     *
     * If it is relative, you will first have to get the current working
     * directory, append the relative path to it and chdir() to the resulting
     * directory.
     *
     * This function should return whatever value chdir() returns.
	 */
    
    //the argument is a absolute path 
    if(is_absolute){
        return chdir(arg);
    }

    //the argument is a absolute path 
    else{
        // get the path to currently working dir
        getcwd(buf, size);

        int len = strlen(buf);
        buf[len] = '/';
        buf[len+1] = '\0';

        // create the absolute path 
        strcat(buf,arg);
  
        int i = chdir(buf);
        free(buf);
        return i;
    }
}

/**
 * `exit` -- exit the shell (builtin command)
 *
 * Terminate the shell process with status 0 using `exit(3)`. This function
 * should never return.
 *
 * You can optionally take an integer argument (a status) and exit with that
 * code.
 */
static int execute_builtin_exit(char *argv[])
{   
    char *arg = argv[1];
    // check if there is a optional input
    int is_optional = (arg && atoi(arg) > 0 );
    // optional 
    if(is_optional){
        exit(atoi(arg));
    }
    // not optional
    else{
        exit(0);
    }
    return EXIT_FAILURE;
}

/**
 * Execute the program specified by `cmd->argv`.
 *
 * Setup any requested redirections for STDOUT, STDIN and STDERR, and then use
 * `execvp` to execute the program.
 *
 * This function should return ONLY IF there is an failure while exec'ing the
 * program. This implies that this function should only be run in a forked
 * child process.
 */
static int run_program(Command *cmd)
{
    /** TODO: Setup redirections.
     *
     * For each non-NULL `in_filename`, `out_filename` and `err_filename` field
     * of `cmd`, perform the following steps:
     *
     *  - Use `open` to acquire a new file descriptor (make sure you have
     *      correct flags and permissions)
     *  - Use `dup2` to duplicate the newly opened file descriptors to the
     *      standard I/O file descriptors (use the symbolic constants
     *      STDOUT_FILENO, STDIN_FILENO and STDERR_FILENO.)
     *  - Use `close` to close the opened file, so as to not leave an open
     *      descriptor across an exec*() call
     */

    /* TODO: Use `execvp` to replace current process with the command program
     *
     * In the case of an error, use `perror` to indicate the name of the
     * command that failed.
     */
    int fd_stdin;
    int fd_stdout;
    int fd_err;
    // if out_file is not NULL the create a out_file with the name cmd->out_filename
    if(cmd->out_filename != NULL){
        // create the out_file 
        fd_stdout = open(cmd->out_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_stdout < 0) {
            perror(cmd->out_filename);
            return EXIT_FAILURE;
        }
        //Make the stdout FD actually be fd_stdout
        if(dup2(fd_stdout,STDOUT_FILENO) < 0){
            perror("dup2");
            return EXIT_FAILURE;            
        }
        close(fd_stdout);
    }
    // if in_file is not NULL the create a out_file with the name cmd->in_filename
    if(cmd->in_filename != NULL){
        // create the in_file 
        fd_stdin = open(cmd->in_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_stdin < 0) {
            perror(cmd->in_filename);
            return EXIT_FAILURE;
        }
        //Make the stdin FD actually be fd_stdin
        if(dup2(fd_stdin,STDIN_FILENO) < 0){
            perror("dup2");
            return EXIT_FAILURE;
        }
        close(fd_stdin);
    }
    // if err_file is not NULL the create a out_file with the name cmd->err_filename
    if(cmd->err_filename != NULL){
        // create the err_file 
        fd_err = open(cmd->err_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_err < 0) {
            perror(cmd->err_filename);
            return EXIT_FAILURE;
        }
        //Make the stderr FD actually be fd_stderr
        if(dup2(fd_err, STDERR_FILENO) < 0){
            perror("dup2");
            return EXIT_FAILURE;
        }
        close(fd_err);
    }

    /* Call `execvp` using all of the arguments we were passed*/
    if(execvp((cmd->argv)[0],cmd->argv)){
        fprintf(stderr, "execvp(\"%s\", ...): ", (cmd->argv)[0]);
        perror("");
        return -1;
    }
    
    
    return EXIT_FAILURE;
}

/**
 * Execute (at least) two Commands connected by a pipe
 */
static int execute_command_with_pipe(Command *cmd)
{
    assert (cmd->pipe_to != NULL);

    /* TODO: Use `pipe(2)` to create a pair of connected file descriptors.
     *
     * These will be used to attach the STDOUT of one command to the STDIN of
     * the next.
     *
     * Be sure to check for and report any errors when creating the pipe.
     */

    /* TODO: Fork a new process.
     *
     * In the child:
     *      - Close the read end of the pipe
     *      - Close the STDOUT descriptor
     *      - Connect STDOUT to the write end of the pipe (the one you didn't close)
     *      - Call `run_program` to run this command
     *
     *  In the parent:
     *      - Fork a second child process
     *      - In child 2:
     *          - Close the write end of the pipe
     *          - Close the STDIN descriptor
     *          - Connect STDIN to the read end of the pipe
     *          - Call `execute_command` to execute the `pipe_to` command
     *      - In the parent:
     *          - Close both ends of the pipe
     *          - Wait for both children to terminate.
     *
     * NOTE: This is a recursive approach. You may find it illuminating instead
     * to consider how you could implement the execution of the whole pipeline
     * in an interative style, using only a single parent, with one child per
     * command. If you wish, feel free to implement this instead of what is
     * outlined above.
     */

    // 0 is read end, 1 is write end
    int pipefds[2];

    // Setup a pair of pipe file descriptors (FD's)
    if (pipe(pipefds) < 0) {
        perror("pipe");
        return EXIT_FAILURE;
    }
    // Fork this process in order to create the first child
    pid_t child1 = fork();
    if(child1 < 0){
        perror("fork");
        return EXIT_FAILURE;
    }
    // in child process
    if (child1 == 0)
    {
        // close read end of the pipe
        close(pipefds[0]);
        // close STDIN
        close(1);

        // Make the stdout FD actually be the write end of the pipe
        if (dup2(pipefds[1], STDOUT_FILENO) < 0) {
            perror("dup2");
            return EXIT_FAILURE;
        }
        run_program(cmd);
        exit(1);       
    }
    else{
        int status1;
        pid_t child2 = fork();
        if(child2 < 0){
            perror("fork");
            return EXIT_FAILURE;
        }

        // in the second child
        if(child2 == 0){
            // close the write end of the pipe
            close(pipefds[1]);
            // close tSTDOUT
            close(0);
            // Make the stdin FD actually be the read end of the pipe
            if (dup2(pipefds[0], STDIN_FILENO) < 0) {
                perror("dup2");
                return EXIT_FAILURE;
            }
            execute_command(cmd->pipe_to);
            exit(2);
        }
        else{

            // close the both end of the pipe
            close(pipefds[0]);
            close(pipefds[1]);

            // wait the second child
            int status2;
            wait(&status2);
        }

        // wait the first child
        wait(&status1);
        return 0;
    }
    return EXIT_FAILURE;
}
