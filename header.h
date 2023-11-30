#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#define PROGRAM_LIMIT 10
#define PIPE_ID '~'
#define OUTPUT_ID '>'

typedef struct SubProgram {
  // ONE stands for a single command
  enum operation { PIPE, OUTPUT, LAST } op;
  char *argv;
  int argv_size;
} SubProgram;

char **str_split(const char *a_str, const char a_delim);
void inspect_programs(SubProgram **programs);
int count_programs(SubProgram **programs);
SubProgram **parse(char **argv, int argc);
void create_pipe(int *fd);

typedef struct {
  int fd[2];
} Pipe;

int create_process_run(SubProgram *argv,
                       void (*child)(SubProgram *program, int pid),
                       Pipe *prev_pipe, Pipe *next_pipe);

void create_pipe(int *fd);
Pipe *new_pipe();
void close_pipe(const Pipe *pipe);
void write_pipe(const Pipe *pipe);
void read_pipe(const Pipe *pipe);

#endif
