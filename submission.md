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
FLAG_GOES_HERE

### Exploit Steps
1. List your steps here

### Patch
```diff
+ Contents of ./diff/problem2.diff goes here
```

### Explanation
In your own words, write a couple sentences about why this code is vulnerable and how you fixed this vulnerability. *(Keep to 200 words or less; preferably much less.)*

---

## problem3

### Flag
FLAG_GOES_HERE

### Exploit Steps
1. List your steps here

### Patch
```diff
+ Contents of ./diff/problem3.diff goes here
```

### Explanation
In your own words, write a couple sentences about why this code is vulnerable and how you fixed this vulnerability. *(Keep to 200 words or less; preferably much less.)*

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
FLAG_GOES_HERE

### Exploit Steps
1. List your steps here

### Patch
```diff
+ Contents of ./diff/problem5.diff goes here
```

### Explanation
In your own words, write a couple sentences about why this code is vulnerable and how you fixed this vulnerability. *(Keep to 200 words or less; preferably much less.)*

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
FLAG_GOES_HERE

### Exploit Steps
1. List your steps here

### Patch
```diff
+ Contents of ./diff/problem7.diff goes here
```

### Explanation
In your own words, write a couple sentences about why this code is vulnerable and how you fixed this vulnerability. *(Keep to 200 words or less; preferably much less.)*

---
