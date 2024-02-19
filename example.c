#include <stdio.h>

void flag() {
  printf("The flag goes here");
}

int main() {
  int num1, num2, num3;

  // Get some valid input for the user's first input
  printf("Enter a number between 1 and 10: ");
  scanf("%d", &num1);
  if (num1 < 1 || num1 > 10) {
    printf("Error: Number must be between 1 and 10.\n");
  } else {
    printf("You entered: %d\n", num1);
  }

  // Get some valid input for the user's second input
  printf("Enter a number between 1 and 10: ");
  scanf("%d", &num2);
  if (num2 < 1 || num2 > 10) {
    printf("Error: Number must be between 1 and 10.\n");
  } else {
    printf("You entered: %d\n", num2);
  }

  int secret;
  // Set the secret value. Hidden from prying eyes...

  // See if the user knows the secret
  if (num1 * num2 == secret) {
    // Do something cool if the user knows the secret
    printf("You guessed the secret number, 42!\n");
    flag();
  } else {
    printf("You did not guess the secret number!\n");
  }
}
