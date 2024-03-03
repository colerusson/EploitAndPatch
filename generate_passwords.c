#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_passwords(char *password, int length, int index) {
  if (index == length) {
    printf("%s\n", password);
    return;
  }
  for (char c = 'a'; c <= 'z'; ++c) {
    password[index] = c;
    generate_passwords(password, length, index + 1);
  }
}

int main() {
  char password[4];
  password[3] = '\0';

  generate_passwords(password, 3, 0);

  return 0;
}
