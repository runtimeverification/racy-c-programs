// Copyright (c) 2015 Runtime Verification Inc. (RV-Predict Team). All Rights Reserved.

#include "bank_account.h"
#include "account.h"
#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;

BankAccount::BankAccount(int id) : Balance(0), Account_Id(id) {}

void BankAccount::Action() {
  // get a random sum in the range [0,MAX_SUM]
  int sum = rand()%MAX_SUM;
  cout << "sum: " << sum << endl;
  // perform action in Bank
  Account::Service(Account_Id,sum);
}

void BankAccount::run() {
  int loop = 2;
  cout << "loop: " << loop << endl;
  // perform action
  for(int i = 0; i< loop; i++){
    Action();
    //sleep a little
    struct timespec tim = {0, 10000000UL}, tim2;
    nanosleep(&tim, &tim2);
  }
  cout << ".";
}

void* BankAccount::run_helper(void* context) {
  ((BankAccount*) context)->run();
  return 0;
}
