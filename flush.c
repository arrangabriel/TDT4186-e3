#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LENGTH 1024

void generate_prompt(char *prmpt, size_t sz)
{
    bzero(prmpt, sz);
    getcwd(prmpt, sz);
    strcat(prmpt, ": ");
}

int run_args(char **args, unsigned int argc)
{
    if (strcmp(args[0], "cd") == 0)
    {
        printf("CD - ran.\n");
    }
    else
    {
        // TODO, search for program in path and return status before forking.
        pid_t pid = fork();
        if (!pid)
        {
            // child
            if (!argc)
                execl(args[0], args[0], NULL);
            else
                execv(args[0], &args[0]);

            printf("Command - %s not found\n", args[0]);
            exit(EXIT_FAILURE);
        }
        // parent
        // TODO - figure out which events to wait on.
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            // Child process called exit
            // Return exit-status of child process
            return WEXITSTATUS(status);
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    char prmpt[MAX_LENGTH];
    char buff[MAX_LENGTH];
    int status;
    generate_prompt(prmpt, sizeof(prmpt));

    while ((status = get_line(prmpt, buff, sizeof(buff))) != NO_INPUT)
    {
        if (status == TOO_LONG)
        {
            printf("Too long\n");
        }
        else
        {
            char **args = (char **)malloc((strlen(buff) / 2) + 2);
            unsigned int argc = parse_line(buff, strlen(buff), &args);
            int status = run_args(args, argc - 1);
            printf("Exit status [%s] = %i\n", buff, status);
            free(args);
        }
    }
    printf("exit\n");
    return EXIT_SUCCESS;
}
