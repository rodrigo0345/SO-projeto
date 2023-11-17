#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROGRAM_LIMIT 10
#define PIPE_ID '~'
#define OUTPUT_ID '>'

// Modifica o fd diretamente
int create_pipe(int *fd) {
  if (pipe(fd) == -1) {
    perror("pipe");
    return 1;
  }
  return 0;
}

char **str_split(const char *a_str, const char a_delim) {
  char **result = 0;
  size_t count = 0;
  const char *tmp = a_str;
  const char *last_comma = 0;
  const char *delim = &a_delim;

  /* Count how many elements will be extracted. */
  while (*tmp) {
    if (a_delim == *tmp) {
      count++;
      last_comma = tmp;
    }
    tmp++;
  }

  /* Add space for trailing token. */
  count += last_comma < (a_str + strlen(a_str) - 1);

  /* Add space for terminating null string so caller
     knows where the list of returned strings ends. */
  count++;

  result = malloc(sizeof(char *) * count);

  if (result) {
    size_t idx = 0;
    const char *start = a_str;
    const char *end = strchr(a_str, a_delim);

    while (end) {
      assert(idx < count);
      size_t size = end - start;
      *(result + idx++) = strndup(start, size);
      start = end + 1;
      end = strchr(start, a_delim);
    }

    assert(idx < count);
    size_t size = strlen(start);
    *(result + idx++) = strndup(start, size);

    // assert(idx == count - 1);
    *(result + idx) = 0;
  }

  return result;
}
typedef struct SubProgram {
  // ONE stands for a single command
  enum operation { PIPE, OUTPUT, LAST } op;
  char *argv;
  int argv_size;
} SubProgram;

void execute_program_sync(SubProgram *program, int pid) {
  // get the first command
  char **f = str_split(program->argv, ' ');
  char **aux_iter = f;

  // Find the last element in argv
  while (*aux_iter != NULL) {
    printf("using: %s\n", *aux_iter);
    if (strcmp(*aux_iter, "") == 0) {
      *aux_iter = NULL;
    }
    aux_iter++;
  }

  printf("Executing program: %s %s %s %s\n", f[0], f[1], f[2], f[3]);
  execvp(f[0], f);

  // If execvp fails, print an error message
  perror("execvp");
  exit(EXIT_FAILURE);
}

// No error handling here
int create_process_run(SubProgram *argv,
                       void (*child)(SubProgram *program, int pid)) {
  int pid = fork();

  if (pid < 0) {
    perror("fork");
  }

  // The parent returns
  if (pid != 0) {
    waitpid(pid, NULL, 0);
    return pid;
  }

  // Execute the child process
  child(argv, pid);

  return pid;
}

// Retorna um conjunto de subprogramas
SubProgram **parse(char **argv, int argc) {

  // concat all strings
  char *all_strings = malloc(sizeof(char) * 500);
  for (int i = 1; i < argc; i++) {
    strcat(all_strings, argv[i]);
    strcat(all_strings, " ");
  }
  printf("%s", all_strings);

  // Init programs
  SubProgram **programs = malloc(sizeof(SubProgram *) * PROGRAM_LIMIT);
  int program_counter = 0;
  for (int i = 0; i < PROGRAM_LIMIT - 1; i++) {
    programs[i] = malloc(sizeof(SubProgram));
    programs[i]->argv_size = 0;
    programs[i]->argv = NULL;
  }

  // split by |
  char **pipe_programs = str_split(all_strings, '|');
  char **iter_pipe_aux = pipe_programs;
  for (; *iter_pipe_aux != NULL; iter_pipe_aux++) {
    // split by >
    char **output_programs = str_split(*iter_pipe_aux, '>');
    char **iter_aux = output_programs;
    for (; *iter_aux != NULL; iter_aux++) {
      printf("%s\n", *iter_aux);

      programs[program_counter++]->argv = *iter_aux;
    }
  }
  return programs;
}

void inspect_programs(SubProgram **programs) {
  printf("Inspect\n");
  for (int i = 0; i < PROGRAM_LIMIT; i++) {
    if (programs[i]->argv == NULL)
      break;
    printf("Program: %d\n", i + 1);
    printf("Argv: %s\n", programs[i]->argv);
  }
}

int main(int argc, char **argv) {
  printf("Running... %d commands\n", argc);
  int fd[2];
  if (create_pipe(fd) == 1) {
    printf("Error creating pipe");
    return 1;
  }

  SubProgram **programs_string = parse(argv, argc);
  inspect_programs(programs_string);

  int pid1 = create_process_run(programs_string[0], execute_program_sync);
  if (pid1 < 0) {
    return 2;
  }
  return 0;
}
