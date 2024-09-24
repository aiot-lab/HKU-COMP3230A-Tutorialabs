#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefds[2];
    pid_t pid;
    const char* message = "Hello from your parent!";
    char buffer[100];

    // Create a pipe
    if (pipe(pipefds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a new process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipefds[1]); // Close the unused write end

        // Read from pipe
        ssize_t num_bytes = read(pipefds[0], buffer, sizeof(buffer));
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Null-terminate the string and print it
        buffer[num_bytes] = '\0';
        printf("Child received: %s\n", buffer);

        // Close the read end of the pipe
        close(pipefds[0]);
    } else {
        // Parent process
        close(pipefds[0]); // Close the unused read end

        // Write to pipe
        if (write(pipefds[1], message, strlen(message)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Close the write end of the pipe to signal the end of writing
        close(pipefds[1]);

        // Wait for the child to finish
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
