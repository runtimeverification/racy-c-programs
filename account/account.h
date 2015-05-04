#ifndef ACCOUNT
#define ACCOUNT
#include "bank_account.h"
#include <vector>

class Account {
  public:
    static int Bank_Total;
    static std::vector<BankAccount*> accounts;
    void go(int, const char**);
    void checkResult(int);
    static void Service(int, int);

  private:
    static const int NUM_ACCOUNTS = 2;
  
  
};
#endif
