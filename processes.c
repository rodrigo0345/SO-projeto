
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// No error handling here, the fe takes -1 if it is the first subprogram, 1 if
// the last and 0 if neither
int create_process_run(SubProgram *argv,
                       void (*child)(SubProgram *program, int pid),
                       Pipe *prev_pipe, Pipe *next_pipe) {
  int pid = fork();
  if (pid < 0) {
    perror("fork");
  }
  // The parent returns
  if (pid != 0) {
    waitpid(pid, NULL, 0);
    return pid;
  }
  // Execute the child proce
  if (prev_pipe != NULL) {
    read_pipe(prev_pipe);
  }
  if (next_pipe != NULL) {
    write_pipe(next_pipe);
  }
  child(argv, pid);
  return pid;
}
