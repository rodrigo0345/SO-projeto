#include "header.h"
#include <stdio.h>
#include <string.h>

void listFiles(FileArray *fileArray, const char *path) {
  struct dirent *dp;
  DIR *dir = opendir(path);

  if (!dir)
    perror("Directory cannot be opened! Closing the program.");
  File *file = malloc(sizeof(File) * MAX);

  int i = 0;
  int size = MAX - 1;
  while ((dp = readdir(dir)) != NULL) {
    // Se tivermos no limite, alocamos mais memoria
    if (i == size - 1) {
      file = realloc(file, sizeof(File) * size * 2);
      size = MAX * 2 - 1;
    }
    file[i++] = (File){dp->d_name};
  }
  free(dp);
  // Close directory stream
  closedir(dir);

  fileArray->files = file;
  fileArray->size = i;
}

const char *file_content_position(char *file, int lineIndex, int wordIndex) {
  wordIndex--;
  if (lineIndex < 0 || wordIndex < 0) {
    return NULL;
  }

  FILE *fp = fopen(file, "r");
  if (fp == NULL) {
    return NULL;
  }

  char buffer[1024];
  int currentLine = 0;

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    if (currentLine == lineIndex) {
      fclose(fp);

      // Tokenize the line into words
      char *token = strtok(buffer, " ");
      int currentWord = 0;

      while (token != NULL) {
        if (currentWord == wordIndex) {
          // Remove trailing newline
          // character if present
          char *newline = strchr(token, '\n');
          if (newline != NULL) {
            *newline = '\0';
          }

          return strdup(token);
        }
        token = strtok(NULL, " ");
        currentWord++;
      }
      // If the specified word index is out
      // of bounds, return NULL
      return NULL;
    }

    currentLine++;
  }

  fclose(fp);

  // If the specified line is not found,
  // return NULL
  return NULL;
}

const char *find_word_in_line(const char *line, const char *word,
                              const char *token_separator) {
  char *token = strtok((char *)line, token_separator);
  while (token != NULL) {
    if (strcmp(token, word) == 0) {
      // Word found in the line
      return line;
    }
    token = strtok(NULL, token_separator);
  }

  // Word not found in the line
  return NULL;
}

const char *find_line_with(const char *file, const char *const word,
                           const char *token_separator) {
  FILE *fp = fopen(file, "r");
  if (fp == NULL) {
    printf("Error opening file %s", file);
    return NULL;
  }

  char buffer[1024];

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    char *aux = malloc(sizeof(buffer) * 1024);
    strcpy(aux, buffer);
    const char *f = find_word_in_line(buffer, word, token_separator);
    if (f != NULL) {
      fclose(fp);
      return aux;
    }
    free(aux);
  }
  fclose(fp);

  // If the word is not found in any line, return NULL
  return NULL;
}
