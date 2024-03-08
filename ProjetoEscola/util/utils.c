#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void clearBuffer(char *string) {
  if ((strlen(string) > 0) && (string[strlen(string) - 1] == '\n')) {
      string[strlen(string) - 1] = '\0';
  }
  else {
      int c;
      while ((c = getchar()) != '\n' && c != EOF);
  }
}
