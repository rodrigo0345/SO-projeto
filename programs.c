#include "header.h"

void inspect_programs(SubProgram **programs) {
  printf("Inspect\n");
  for (int i = 0; i < PROGRAM_LIMIT; i++) {
    if (programs[i]->argv == NULL)
      break;
    printf("Program: %d\n", i + 1);
    printf("Argv: %s\n", programs[i]->argv);
  }
}
int count_programs(SubProgram **programs) {
  int count = 0;
  for (int i = 0; i < PROGRAM_LIMIT; i++) {
    if (programs[i]->argv == NULL)
      break;
    count++;
  }
  return count;
}
int count_pipes(SubProgram **programs) {
  int count = 0;
  for (int i = 0; i < PROGRAM_LIMIT; i++) {
    if (programs[i]->argv == NULL)
      break;
    else if (programs[i]->op == PIPE) {
      count++;
    }
  }
  return count;
}
