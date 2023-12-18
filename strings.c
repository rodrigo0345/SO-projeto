#include "header.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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

// Retorna um conjunto de subprogramas
SubProgram **parse(char **argv, int argc) {
  // concat all strings
  char *all_strings = malloc(sizeof(char) * 500);
  for (int i = 1; i < argc; i++) {
    strcat(all_strings, argv[i]);
    strcat(all_strings, " ");
  }
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

  iter_pipe_aux = pipe_programs;

  for (; *iter_pipe_aux != NULL; iter_pipe_aux++) {

    if (*(iter_pipe_aux + 1) != NULL)
      strcat(*iter_pipe_aux, " @");

    // split by >
    char **output_programs = str_split(*iter_pipe_aux, '>');
    char **iter_aux = output_programs;
    for (; *iter_aux != NULL; iter_aux++) {
      // checka a ver se tem um comando a seguir
      if (*(iter_aux + 1) != NULL)
        strcat(*(iter_aux + 1), " >");

      programs[program_counter++]->argv = *iter_aux;
    }
  }

  // percorremos os programas novamente e vemos setem > no final ou @ no final
  for (int i = 0; i < program_counter; i++) {
    char last_char = programs[i]->argv[strlen(programs[i]->argv) - 1];
    if (last_char == '@') {
      programs[i]->op = PIPE;
      last_char = '\0';
    } else if (last_char == '>') {
      // Normalmente apenas existe um ficheiro para redirecionar o output
      // ent vou colocar no inicio do array
      programs[i]->op = OUTPUT;
      if (i == 0) {
        perror("Error, no input program");
      }

      trimString(programs[i]->argv);
      char **s = str_split(programs[i]->argv, ' ');
      programs[i]->argv = s[0];

      // trocar de lugar com o anterior para podermos trocar o output a tempo
      SubProgram *aux = programs[i];
      programs[i] = programs[0];
      programs[0] = aux;

      // voltar a colocar o programa no sitio inicial
      for (int j = program_counter; j > 1; j--) {
        if (programs[j]->argv == NULL)
          continue;
        else {
          SubProgram *aux = programs[j];
          programs[j] = programs[j - 1];
          programs[j - 1] = aux;
        }
      }

      last_char = '\0';
    } else {
      programs[i]->op = LAST;
      last_char = '\0';
    }
  }

  return programs;
}

void add_identifier(char ***string, char *id) {
  char **iter_pipe_aux = *string;

  // Add the identifier of the operation to the end
  for (; *iter_pipe_aux != NULL; iter_pipe_aux++) {
    if (*iter_pipe_aux != NULL)
      strcat(*iter_pipe_aux, id);
  }
}

int str_length(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    i++;
  }
  return i;
}

void trimString(char *str) {
  int start = 0, end = strlen(str) - 1;

  // Remove leading whitespace
  while (isspace(str[start])) {
    start++;
  }

  // Remove trailing whitespace
  while (end > start && isspace(str[end])) {
    end--;
  }

  // If the string was trimmed, adjust the null terminator
  if (start > 0 || end < (strlen(str) - 1)) {
    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
  }
}
