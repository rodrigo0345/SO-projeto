#include "header.h"
#include <unistd.h>

#ifndef MAX_BUFFER_SIZE
#define MAX_BUFFER_SIZE 1024
#endif

int countActiveUsers() {
  FILE *utmpFile = fopen("/var/run/utmp", "r");
  int userCount = 0;

  if (utmpFile != NULL) {
    char buffer[MAX_BUFFER_SIZE];
    while (fgets(buffer, MAX_BUFFER_SIZE, utmpFile) != NULL) {
      if (buffer[0] != '\0') {
        userCount++;
      }
    }
    fclose(utmpFile);
  }

  return userCount;
}
