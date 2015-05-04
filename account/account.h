#include "bank_account.h"

class Account {
  public:
    static int Bank_Total;
    static BankAccount* accounts;
    BankAccount(void);
    void go(int, const char**);
    void checkResult(int);
    static void Service(int, int);

  private:
    static const int NUM_ACCOUNTS = 2;
  
  
};
