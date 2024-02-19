#include <stdio.h>

void flag() {
  printf("The flag goes here");
}

void VIP() {
  printf("Hello VIP user!\n");
  flag();
}

// Bank account class. Just keeps track of the user's balance.
struct user_account {
  int account_balance;
};

// Get the user's account balance
int get_account_balance(struct user_account *u) {
  return u->account_balance;
}

// Set the user's account balance
void set_account_balance(int amount, struct user_account *u) {
  u->account_balance = amount;
}

// Update the account balance when there is a withdraw
int update_account_balance(int amount, struct user_account *u) {
  u->account_balance = u->account_balance - amount;
  return u->account_balance;
}

// Check to make sure the user has enough money to process the withdrawal
int check_withdraw_amount(int amount, struct user_account *u) {
  return amount < get_account_balance(u);
}

// Handle a large withdraw
void large_withdraw(struct user_account *u) {
  unsigned int withdrawal;

  printf("How much would you like to withdraw?\n> ");
  scanf("%u", &withdrawal);
  withdrawal += 50;

  // Ensure the user has enough money to complete the transaction
  if (!check_withdraw_amount(withdrawal, u)) {
    printf("Sorry, you do not have enough funds to complete this withdrawal.\n");
    printf("Have a good day!\n");
    return;
  }

  printf("Great! Withdrawing $%d...\n", withdrawal);
  update_account_balance(withdrawal, u);
  printf("Your new balance is $%d\n", get_account_balance(u));
}

// Handle a small withdraw
void small_withdraw(struct user_account *u) {
  unsigned char withdrawal;

  printf("How much would you like to withdraw?\n>");
  scanf("%u", &withdrawal);

  // Ensure the user has enough money to complete the transaction
  if (!check_withdraw_amount(withdrawal, u)) {
    printf("Sorry, you do not have enough funds to complete this withdrawal.\n");
    printf("Have a good day!\n");
    return;
  }

  printf("Great! Withdrawing $%d...\n", withdrawal);
  update_account_balance(withdrawal, u);
  printf("Your new balance is $%d\n", get_account_balance(u));
}

int main() {
  struct user_account user;
  int balance, choice_num;

  // Set up a new account for the user
  user.account_balance = 15000;

  // Greeting the user
  balance = get_account_balance(&user);
  printf("Hello, welcome to your Banking Application.\n");
  printf("You currently have $%d in your account.\n\n", balance);

  // Ask what the user would like to do
  printf("Is this a withdrawal or ATM transaction?\n");
  printf("[1] Withdrawal (>= $250, $50 Fee)\n");
  printf("[2] ATM Transaction (<= $250, No Fee)\n");

  // Ask the user for which option they want.
  while (1) {
    // Verify input
    if (!choice_num) {
      choice_num = -1;
    }
    if (choice_num == 1 || choice_num == 2)
      break;

    // If we get invalid input, re-prompt the user until we get valid input
    printf("Which option do you want?\n> ");
    if (scanf("%d", &choice_num) != 1) {
      choice_num = -1;
    }
  }

  // Process the withdrawal
  if (choice_num == 1)
    large_withdraw(&user);
  else
    small_withdraw(&user);

  // Users with over $1,000,000 have some special functionality.
  int vip_amount = 1000000;
  if (get_account_balance(&user) > vip_amount)
    VIP();
  else
    printf("Have a good day!\n");
}