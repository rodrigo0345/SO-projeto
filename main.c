#include "./header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void execute_program_sync(SubProgram *program, int pid) {
  // get the first command
  trimString(program->argv);
  char **f = str_split(program->argv, ' ');
  char **aux_iter = f;

  // Find the last element in argv
  while (*aux_iter != NULL) {
    if (strcmp(*aux_iter, "") == 0) {
      *aux_iter = NULL;
      break;
    }
    aux_iter++;
  }
  printf("Executing program: %s %s %s %s\n", f[0], f[1], f[2], f[3]);
  execvp(f[0], f);

  // If execvp fails, print an error message
  perror("execvp");
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  printf("Running... %d commands\n", argc);

  SubProgram **programs_string = parse(argv, argc);
  int num_pipes = count_programs(programs_string) - 1;
  printf("Number of pipes: %d\n", num_pipes);

  Pipe pipes[num_pipes];
  for (int i = 0; i < num_pipes; i++) {
    pipes[i] = *new_pipe();
  }

  for (int i = 0; i < num_pipes + 1; i++) {
    printf("Current process %s\n", programs_string[i]->argv);
    Pipe *prev = i == 0 ? NULL : &pipes[i - 1];
    Pipe *next = i == num_pipes ? NULL : &pipes[i];
    printf("Prev: %p, Next: %p\n", prev->fd, next->fd);

    int pid1 = create_process_run(programs_string[i], execute_program_sync,
                                  prev, next);

    if (pid1 < 0) {
      exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}
