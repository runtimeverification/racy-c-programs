#ifndef BANK_ACCOUNT
#define BANK_ACCOUNT
#include <pthread.h>

class BankAccount {
  public:
    pthread_t thread;
    int Balance;
    int Account_Id;
    BankAccount(int);
    static const int MAX_SUM = 300;
    
    void Action();
    void run();
    
    static void* run_helper(void*);

};
#endif
