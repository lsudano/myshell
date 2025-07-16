#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024

int main() {
    char line[MAX_LINE];

    while (1) {
        printf("> ");
        if (fgets(line, MAX_LINE, stdin) == NULL) continue;

        line[strcspn(line, "\n")] = 0; // remove newline

        if (line[0] == '\0') continue;

        // Parse input into args
        char *args[64];
        char *token = strtok(line, " ");
        int i = 0;

        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) continue; // no command

        // Handle "exit"
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // Handle "cd"
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: expected argument\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("cd failed");
                }
            }
            continue; // don't fork for cd
        }

        // Run external command
        pid_t pid = fork();
        if (pid == 0) {
            // child process
            execvp(args[0], args);
            perror("exec failed");
            exit(1);
        } else if (pid > 0) {
            // parent waits
            wait(NULL);
        } else {
            perror("fork failed");
        }
    }

    return 0;
}
