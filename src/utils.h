#ifndef __UTILS_H__
#define __UTILS_H__

#include "list.h"
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define RESET "\x1B[0m"
#define KREDB "\x1B[31;1m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KCYNB "\x1B[36;1m"
#define KBLU "\x1B[34m"
#define KWHT "\x1B[37m"

/**
 * @brief Generates a prompt string
 *
 * @param prmpt The string to be populated
 * @param sz The size of prmpt
 */
void generate_prompt(char *prmpt, size_t sz);

/**
 * @brief Checks for finished background jobs, and removes them from the list
 *
 * @return Status 
 */
int refresh_jobs(List *jobs);

/**
 * @brief Get io filedescriptors from command
 *
 * @param cmd The command struct to get from
 * @param input_fd The input file descriptor
 * @param output_fd The output file descriptor
 *
 * @return Status
 */
int get_io(Command *cmd, int *input_fd, int *output_fd);

#endif