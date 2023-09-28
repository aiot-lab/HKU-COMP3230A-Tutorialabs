#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    // Create pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        return -1;
    }

    // First fork
    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("fork");
        return -1;
    } else if (pid1 == 0) {
        // Child 1: executing ls command
        
        // stdout will write to the write part of the pipe
        dup2(fd[1], 1);
        
        // Child does not need read end, close it
        close(fd[0]);
        
        execlp("ls", "ls", NULL);
    } else {
        // Second fork
        pid_t pid2 = fork();

        if (pid2 < 0) {
            perror("fork");
            return -1;
        } else if (pid2 == 0) {
            // Child 2: executing wc command
            
            // stdin will read from the read part of the pipe
            dup2(fd[0], 0);
            
            // Child does not need write end, close it
            close(fd[1]);
            
            execlp("wc", "wc", "-l", NULL);
        } else {
            // Parent process
            
            // Parent does not need any ends of the pipe, close them
            close(fd[0]);
            close(fd[1]);
            
            // Wait for both children to finish
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }
    return 0;
}