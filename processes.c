
#include "header.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int create_process_run(SubProgram *argv,
                       void (*child)(SubProgram *program, int pid),
                       Pipe *prev_pipe, Pipe *next_pipe, int output_fd,
                       int input_fd) {
  int pid = fork();
  if (pid < 0) {
    perror("fork");
  }
  // The parent returns
  if (pid != 0) {
    if (prev_pipe != NULL)
      close_pipe(prev_pipe);
    waitpid(pid, NULL, 0);
    return pid;
  }
  // Execute the child proce
  if (prev_pipe != NULL) {
    read_pipe(prev_pipe, input_fd);
  }
  if (next_pipe != NULL) {
    write_pipe(next_pipe, output_fd);
  }

  // run the child in the new process
  child(argv, pid);

  return pid;
}

int get_fd(SubProgram *argv) {
  int fd = open(argv->argv, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (fd == -1) {
    perror("Error opening the destination file");
    exit(EXIT_FAILURE);
  }

  return fd;
}
