#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

void flag() {
  printf("The flag goes here");
}

int main() {
  // Get the name of a tempfile we can use. It won't exist yet.
  char destinationFile[1024];
  snprintf(destinationFile, sizeof(destinationFile) - 1, "/tmp/%d", getpid());

  if (access(destinationFile, F_OK) == 0) {
    printf("Hey, you shouldn't have access to my file... What are you trying to pull? Go away!\n");
  } else {
    // I'm tired. Checking access is hard work... I need some sleep. 0.1 seconds should do it.
    usleep(100000);

    // Check if the file exists before attempting to open it
    if (access(destinationFile, F_OK) == 0) {
      printf("Error: File already exists.\n");
    } else {
      // Ok, let's open this file and write the flag to it.
      // Now we can write to the file without worrying about race conditions.
      int outFile = open(destinationFile, O_WRONLY | O_CREAT, 0644);
      if (outFile == -1) {
        printf("Error: Unable to create/open the file.\n");
      } else {
        flag();
        close(outFile);
      }
    }
  }
}
