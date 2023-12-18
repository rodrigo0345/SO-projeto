#ifndef HEADER_H
#define HEADER_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#define PROGRAM_LIMIT 10
#define MAX 100
#define PIPE_ID '~'
#define OUTPUT_ID '>'

typedef struct {
  char *name;
} File;

typedef struct {
  File *files;
  int size;
} FileArray;

typedef struct time_plus {
  long seconds;
  long minutes;
  long hours;
} Time;

typedef struct {
  long shr;
  double cpu_usage;
  double mem_usage;
  Time time;
  const char *command;
  const char *s;
  long virt;
  const char *res;
  const char *ni;
  char *user;
  char *pid;
  int running;
  char *pr;
} ProcessInfo;

typedef struct {
  ProcessInfo *processes;
  int size;
} ProcessInfoArray;

typedef struct {
  Time uptime;
  int n_users;
  struct Load {
    double oneMinute;
    double fiveMinutes;
    double fifteenMinutes;
  } load;
  long total_tasks;
  long running_tasks;
  ProcessInfoArray processes;
} SystemInfo;

// usado para ler os conteudos de /proc
void listFiles(FileArray *fileArray, const char *path);

typedef struct SubProgram {
  // ONE stands for a single command
  enum operation { PIPE, OUTPUT, LAST } op;
  char *argv;
  int argv_size;
} SubProgram;

char **str_split(const char *a_str, const char a_delim);
void trimString(char *str);
void inspect_programs(SubProgram **programs);
int count_programs(SubProgram **programs);
SubProgram **parse(char **argv, int argc);
void create_pipe(int *fd);
const char *file_content_position(char *file, int lineIndex, int wordIndex);
const char *find_line_with(const char *file, const char *const word,
                           const char *token_separator);
const char *find_word_in_line(const char *line, const char *word,
                              const char *token_separator);
int count_pipes(SubProgram **programs);
int get_fd(SubProgram *argv);

int str_length(char *str);

typedef struct {
  int fd[2];
} Pipe;

int create_process_run(SubProgram *argv,
                       void (*child)(SubProgram *program, int pid),
                       Pipe *prev_pipe, Pipe *next_pipe, int input_fd,
                       int output_fd);

void create_pipe(int *fd);
Pipe *new_pipe();
void close_pipe(const Pipe *pipe);
void write_pipe(const Pipe *pipe, int fd);
void read_pipe(const Pipe *pipe, int fd);

int countActiveUsers();
void getMemoryInfo();
void getSwapInfo();
void getCpuUsage();

#endif
