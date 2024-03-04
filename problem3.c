#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void flag() {
  printf("The flag goes here");
}

// Check the password
bool checkPassword(char *input) __attribute__((stack_protect));
bool checkPassword(char *input) {
  char passwordBuffer[16];
  const char secret[16] = "secret_password";

  // Check that the passwords match securely
  strncpy(passwordBuffer, input, sizeof(passwordBuffer)); // Use strncpy for safety

  for (size_t i = 0; i < sizeof(passwordBuffer); i++) {
    passwordBuffer[i]++;
  }

  // Secure comparison
  if (memcmp(secret, passwordBuffer, sizeof(secret)) != 0) {
    printf("Access denied!\n");
    return false;
  }

  return true;
}

int main(int argc, char **argv) {
  // Basic command line argument checking
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <password>\n", argv[0]);
    return 0;
  }

  if (checkPassword(argv[1])) {
    flag();
  }
}
