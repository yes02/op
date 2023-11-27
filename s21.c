#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("I am Child Process (PID: %d)\n", getpid());
    } else if (pid > 0) {
        // Parent process
        printf("I am Parent Process (PID: %d)\n", getpid());
    } else {
        perror("fork");
    }

    return 0;
}
