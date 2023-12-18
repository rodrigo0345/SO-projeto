#include "header.h"
#include <stdlib.h>
#include <unistd.h>

void create_pipe(int *fd);
Pipe *new_pipe() {
  Pipe *p = (Pipe *)malloc(sizeof(Pipe));
  create_pipe(p->fd);
  return p;
}

void close_pipe(const Pipe *pipe) {
  close(pipe->fd[0]);
  close(pipe->fd[1]);
}

// fd é para o input e output
void write_pipe(const Pipe *pipe, int fd) {
  if (dup2(pipe->fd[1], fd) == -1) {
    perror("dup2");
    exit(EXIT_FAILURE);
  }
  close_pipe(pipe);
}

void read_pipe(const Pipe *pipe, int fd) {
  dup2(pipe->fd[0], fd);
  close_pipe(pipe);
}

void create_pipe(int *fd) {
  if (pipe(fd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
}
