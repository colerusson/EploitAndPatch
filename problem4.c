#include <stdio.h>

void flag() {
  printf("The flag goes here");
}

// Do not change this value.
static const int reset_key = -504;

int main() {
  int value, factor, result, password;

  // This is a simple calculator with some input checking
  printf("Enter a value: ");
  if (scanf("%d", &value) != 1) {
    printf("Invalid input, not a number.\n");
    return -1;
  }
  if (value < 0) {
    printf("Invalid input. Value must be a positive integer!\n");
    return -1;
  }

  printf("Enter a multiple: ");
  if (scanf("%d", &factor) != 1) {
    printf("Invalid input, not a number.\n");
    return -1;
  }
  if (factor < 0) {
    printf("Invalid input. Multiple must be a positive integer!\n");
    return -1;
  }

  result = value * factor;

  if (result < 0) {
    printf("Error: Result is negative!\n");
    return -1;
  }

  if (result == reset_key) {
    // reset_key is only usable by admins, normal users shouldn't worry about it...
    // Plus it's not like you can multiple 2 positive numbers to get a negative number anyway...
    flag();
  } else {
    printf("Product: %d\n", result);
  }
}