#include "account.h"

void Account::go(int argc, const char** argv) {
  Bank_Total = 0;
  accounts = new BankAccount[NUM_ACCOUNTS];
}
