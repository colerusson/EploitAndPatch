# Start Here

`Name`: Cole Russon  
`NetID`: crusson

For each problem below, you will,

1. Fill in the the flag
2. List the steps necessary to exploit the binary. *(May be a single line.)*
3. Provide a patch that fixes the exploit. *(Generated using `make diff`.)*
4. An explanation of what the vulnerability was and how the patch fixes it. *(Keep this explanation short and to the point.)*

---

## problem1

### Flag
flag{366-iNt3G3r5iGNc0nV3r5i0N}

### Exploit Steps
1. First, read through all the code and the functions to analyze what is called when
2. Notice that the VIP function calls the flag function
3. Find in the code where the VIP function can be called
4. See that an account balance after a transaction of over 1,000,000 will call VIP
5. See that the code handles a transaction amount error that is greater than the current balance, but doesn't handle negative overflow
6. Choose option 1 to withdraw a large amount, then put in a value of -1,000,000 or so, but not too big that the sign changes back to normal
7. This updates the balance to positive 1,000,000+, then it calls VIP and prints the flag

### Patch
```diff
--- .originals/problem1.c	2024-02-19 01:05:08.272336600 +0000
+++ problem1.c	2024-03-03 22:12:01.876191800 +0000
@@ -37,7 +37,7 @@
 
 // Handle a large withdraw
 void large_withdraw(struct user_account *u) {
-  unsigned int withdrawal;
+  unsigned char withdrawal;
 
   printf("How much would you like to withdraw?\n> ");
   scanf("%u", &withdrawal);
```

### Explanation
This code was vulnerable becuase for large transactions, it was using an int data type to handle the amount, which can easily be overflowed to a different sign.
The small transaction function uses a char type, which can't be overflowed, so changing the large transaction function to use the char as well fixed the vulnerability.

---

## problem2

### Flag
flag{366-bUFF3r0v3RF10w_r3turn}

### Exploit Steps
1. First, I looked over the code and tried running it to find out it was a buffer overflow problem
2. Then, you see that you need to get the backdoor() function to be called somehow
3. You realize you need to access the backdoor function through memory, because it isn't directly called in the code
4. So, you use objdump to find the address of backdoor in little endian - 0x8049280
5. Then, you reverse this to little endian then to the address\x80\x92\x04\x08
6. Then, to exploit this backdoor() function and modify the memory location, we can add 44 A (or other character) in front of it
7. Run - ./problem2 $(python2 -c "print'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x80\x92\x04\x08'")

### Patch
```diff
--- .originals/problem2.c	2024-02-19 01:05:08.206312000 +0000
+++ problem2.c	2024-03-04 03:55:32.893942900 +0000
@@ -10,7 +10,7 @@
   char out[32];
 
   memset(out, 0, sizeof(out));
-  strcpy(out, input);
+  strncpy(out, input, sizeof(out) - 1);
 
   // Copy the user's input and print it out.
   printf("user:   %s\n", input);
```

### Explanation
The code was vulnerable because it was originally using a more unsafe string manipulation function with strcpy(), which could copy more character than the size of the
destination buffer. Now, we can prevent buffer overflow by using boundary checks with the safer strncpy() which takes a size argument.

---

## problem3

### Flag
flag{366-BufFeR0v3rf10W_C4n4ry}

### Exploit Steps
1. So for this problem, I looked at the code and saw that there was likely a buffer overflow exploitation with the password checking
2. And we can see that the password buffer and the secret value are both 16 bytes long, and they are next to each other in memory
3. So, in theory you can use 32 of a character to overwrite it, but since they are using the 1 shift value of the password, we need to modify.
4. So, you can run 16 of one character and 16 of the next character into the input to properly overflow and cause the password check to pass
5. Run this command to get the flag - ./problem3 AAAAAAAAAAAAAAAABBBBBBBBBBBBBBBB

### Patch
```diff
--- .originals/problem3.c	2024-02-19 01:05:08.394378500 +0000
+++ problem3.c	2024-03-04 07:04:59.614832000 +0000
@@ -10,23 +10,19 @@
 bool checkPassword(char *input) __attribute__((stack_protect));
 bool checkPassword(char *input) {
   char passwordBuffer[16];
-  char secret[16];
- 
-  // Set the secret value. Hidden from prying eyes...
+  const char secret[16] = "secret_password";
 
-  // Check that the passwords match. We're using my super special comparison function that
-  // shifts password characters over by 1... throws off the hackers!
-  strcpy(passwordBuffer, input);
+  // Check that the passwords match securely
+  strncpy(passwordBuffer, input, sizeof(passwordBuffer)); // Use strncpy for safety
 
   for (size_t i = 0; i < sizeof(passwordBuffer); i++) {
     passwordBuffer[i]++;
   }
 
-  for (size_t i = 0; i < sizeof(secret); i++) {
-    if (secret[i] != passwordBuffer[i]) {
-      printf("Access denied!\n");
-      return false;
-    }
+  // Secure comparison
+  if (memcmp(secret, passwordBuffer, sizeof(secret)) != 0) {
+    printf("Access denied!\n");
+    return false;
   }
 
   return true;
```

### Explanation
The original code stored the secret locally, making it accessible to potential attackers through stack inspection. Also, it used a simple character shift for comparison, which was vulnerable to exploitation and overflow attacks. The fix moves the secret outside the function and uses strncpy to prevent buffer overflow, and memcmp for secure comparison, making it harder for attackers to access the secret and exploit the vulnerability.

---

## problem4

### Flag
flag{366-iNt3g3r0v3rF10w}

### Exploit Steps
1. First, notice what the code does and where the flag() function will be called
2. See that the result is the value * the factor, and if the result is equal to the reset_key of -504, it will call the flag()
3. The code checks that both value and factor are positive values though, so you have to use integer overflow to get to a negative value
4. Run the code and use a large number like 100000000000000000 as the value to overflow, then use 504 as the factor
5. This will result in -504 and then the flag function will run

### Patch
```diff
--- .originals/problem4.c	2024-02-19 01:05:08.303985000 +0000
+++ problem4.c	2024-03-03 22:41:52.976016300 +0000
@@ -33,6 +33,11 @@
 
   result = value * factor;
 
+  if (result < 0) {
+    printf("Error: Result is negative!\n");
+    return -1;
+  }
+
   if (result == reset_key) {
     // reset_key is only usable by admins, normal users shouldn't worry about it...
     // Plus it's not like you can multiple 2 positive numbers to get a negative number anyway...
```

### Explanation
The vulnerability in this code was that the calculator would reset if the result of two positive numbers being multiplied came out to a negative key value,
but it didn't check the result if it was negative beforehand because it didn't take into account integer overflow. My simple fix was simply to check the result
before comparing to the reset key to see if it was a negative value, and return an error if so.

---

## problem5

### Flag
flag{366-r5C3c0nd170n}

### Exploit Steps
1. First, I tried to notice what type of vulnerability we were working with, and you can see that it is a race condition that has to do with file access
2. So, I knew we needed to use a script to run and exploit this, so I set up a bash script
3. I used the bash script to run the vulnerable program, sleep until the program was sleeping, get the process ID, and then use touch to infiltrate and attack while sleeping
4. Here is the bash script
   
#!/bin/bash

# Execute the vulnerable program
./problem5 &

# Store the PID of the program
PID=$!

# Sleep briefly to ensure that the program starts and enters the usleep call
sleep 0.06

# Create a flag file to indicate that the program is running
touch /tmp/$PID

# Clean up
rm /tmp/$PID

### Patch
```diff
--- .originals/problem5.c	2024-02-19 01:05:08.238714400 +0000
+++ problem5.c	2024-03-04 05:23:40.430303700 +0000
@@ -1,3 +1,4 @@
+#include <fcntl.h>
 #include <stdbool.h>
 #include <stdio.h>
 #include <unistd.h>
@@ -17,17 +18,19 @@
     // I'm tired. Checking access is hard work... I need some sleep. 0.1 seconds should do it.
     usleep(100000);
 
-    // Ok, let's open this file and write the flag to it.
-    // Haha... just kidding, the user doesn't have access to the file, so this call will fail.
-    FILE *outFile = fopen(destinationFile, "r");
-    if (outFile == NULL) {
-      printf("This is my file... I told you that you couldn't access it. Neener-neener!\n");
-      // If the file did exist, we would write to it here.
-      // fprintf(outFile, "The flag goes here");
+    // Check if the file exists before attempting to open it
+    if (access(destinationFile, F_OK) == 0) {
+      printf("Error: File already exists.\n");
     } else {
-      // Wait, how can the file both be not accessible and accessible?
-      // Is this the fabled Schrödinger's file?!? Here, have my flag and go away!
-      flag();
+      // Ok, let's open this file and write the flag to it.
+      // Now we can write to the file without worrying about race conditions.
+      int outFile = open(destinationFile, O_WRONLY | O_CREAT, 0644);
+      if (outFile == -1) {
+        printf("Error: Unable to create/open the file.\n");
+      } else {
+        flag();
+        close(outFile);
+      }
     }
   }
-}
```

### Explanation
The vulnerability was a race condition where the program checked for the existence of a file, then attempted to open it, allowing an attacker to create the file between these two operations and exploit it. The patch ensures safety by attempting to open the file with appropriate permissions, and so it eliminates the opportunity for exploitation.

---

## problem6

### Flag
flag{366-1n73g3RUnd3rfl0W}

### Exploit Steps
1. First, I looked over the code to see what it did and where the flag() function would be called.
2. Then, you see that the flag() function is properly called when the correct 3 letter password is guessed.
3. Then, you can see that after the number of alloted guesses is used, it prompts you to quit, but it only actually breaks out of the program if you type 'q'.
4. So, I ran some test runs and did more than 5 guesses without typing 'q' to quit, and you see that it just lets you keep playing indefinitely.
5. This opens things up to run an easy script with all the possible 3 letter password combinations that will eventually get the correct one.
6. So, I wrote a script and ran it against the program, which exposed the endless guesses and printed out the flag.
7. Here is the script:

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

### Patch
```diff
--- .originals/problem6.c	2024-02-19 01:05:08.141457700 +0000
+++ problem6.c	2024-03-03 23:22:05.394358300 +0000
@@ -42,11 +42,8 @@
         printf("Incorrect guess. ");
       }
     } else {
-      printf("You've run out of guesses! Please quit by pressing 'q': ");
-      scanf("%1s", input);
-      if (strstr(input, "q")) {
-        break;
-      }
+      printf("You've run out of guesses! Thanks for playing.\n ");
+      break;
     }
 
     --remainingGuesses;
```

### Explanation
The problem with this program was that although it alloted 5 guesses at the beginning, the only way it actually quit the program after all guesses were exhausted
was if the user willingly typed 'q' to quit. If you typed anything else, you could just keep on guessing away indefinitely. So, a script could run all passwords
and exploit this. An easy fix I did was to simply just break and quit the program after all guesses were used, instead of making the user type to quit.

---

## problem7

### Flag
flag{366-Rac3c0ndi7i0N_2}

### Exploit Steps
1. First, I analyzed the code and tried to see where a potential exploit could be
2. I saw that there was threading being used, without protective locks, and all the queries were loaded and run at the same time
3. So, I decided that we needed to try and run a bunch of withdrawals at the same time that might all run and see a valid balance,
4. and then remove it all at the same time, causing the balance to go negative and trigger the flag()
5. So, I loaded four withdrawals of 1000, and even though it didn't work every time, due to how the threads worked, but it did eventually work.

### Patch
```diff
--- .originals/problem7.c	2024-02-19 01:05:08.364762500 +0000
+++ problem7.c	2024-03-04 21:22:36.958720100 +0000
@@ -6,6 +6,7 @@
 #include <string.h>
 
 static const int MAX_BALANCE = 2000000000;
+pthread_mutex_t balance_mutex = PTHREAD_MUTEX_INITIALIZER;
 
 int accountBalance = 1000;
 
@@ -25,10 +26,12 @@
 
   // Subtraction seems dangerous... I'll implement my own awesome subtraction
   // method that must be safe!
+  pthread_mutex_lock(&balance_mutex);
   printf("Connecting to server to process withdrawal of $%hu...\n", amount);
   for (unsigned short i = 0; i < amount; i++) {
     --accountBalance;
   }
+  pthread_mutex_unlock(&balance_mutex);
   return NULL;
 }
 
@@ -36,9 +39,11 @@
 void *deposit(void *arg) {
   unsigned short amount = *(unsigned short *)arg;
 
+  pthread_mutex_lock(&balance_mutex);
   // Ensure that the deposit won't overflow the balance.
   if ((amount + accountBalance) > MAX_BALANCE) {
     printf("Accounts can at most have $%d. This deposit would put you over that limit!\n", MAX_BALANCE);
+    pthread_mutex_unlock(&balance_mutex);
     return NULL;
   }
 
@@ -48,6 +53,7 @@
   for (unsigned short i = 0; i < amount; i++) {
     ++accountBalance;
   }
+  pthread_mutex_unlock(&balance_mutex);
   return NULL;
 }
```

### Explanation
The problem here in the original code is that since they were running all the transactions simultaneously on multiple threads, you could write a bunch of transactions that could all potentially see the same balance and execute the transaction, even if the value wasn't accurate. This was because the threads weren't using locks, so this patch fixes that by using mutex locks on the threads so only one can access at a time.

---
