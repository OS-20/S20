#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void typeline_all(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { printf("File not found!\n"); return; }
    char line[256];
    while (fgets(line, sizeof(line), fp)) printf("%s", line);
    fclose(fp);
}

int main() {
    char input[100], *arg[5];

    while (1) {
        printf("myshell$ ");
        if (!fgets(input, sizeof(input), stdin)) break;

        int i = 0;
        arg[i] = strtok(input, " \t\n");
        if (!arg[i]) continue;
        while ((arg[++i] = strtok(NULL, " \t\n")));

        if (!strcmp(arg[0], "exit")) break;
        else if (!strcmp(arg[0], "typeline") && arg[1] && arg[1][0]=='-' && arg[1][1]=='a' && arg[2])
            typeline_all(arg[2]);
        else {
            if (fork() == 0) {
                execvp(arg[0], arg);
                perror("Command failed");
                exit(1);
            } else wait(NULL);
        }
    }
    return 0;
}
