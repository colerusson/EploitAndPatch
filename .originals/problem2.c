#include <stdio.h>
#include <string.h>

void flag();
void backdoor();

// chatbots have to start somewhere...
void parrot(char *input) {
  // Take the user input and run it through our chat algorithm
  char out[32];

  memset(out, 0, sizeof(out));
  strcpy(out, input);

  // Copy the user's input and print it out.
  printf("user:   %s\n", input);
  printf("parrot: %s\n", out);
}

int main(int argc, char **argv) {
  if (argc == 1) {
    printf("Usage: %s <input string>\n", argv[0]);
  } else {
    parrot(argv[1]);
  }
}

void flag() {
  printf("The flag goes here");
}

// Too bad this function is never called...
void backdoor() {
  flag();
  printf("Success!\n");
}
