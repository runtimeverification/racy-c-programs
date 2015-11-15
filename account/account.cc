// Copyright (c) 2015 Runtime Verification Inc. (RV-Predict Team). All Rights Reserved.

#include "account.h"
#include <pthread.h>
#include <stdlib.h>

#include<iostream>
#include<vector>
using namespace std;

int Account::Bank_Total = 0;
vector<BankAccount*> Account::accounts;

void Account::go(int argc, const char** argv) {
  accounts.clear();
  
  // create all accounts
  for(int i = 0; i< NUM_ACCOUNTS; i++){
    accounts.push_back(new BankAccount(i));
  }
  
  cout << "Bank system started" << endl;
  
  // start all accounts
  for(int i = 0; i< NUM_ACCOUNTS; i++){
    pthread_create(&(accounts[i]->thread), NULL, &BankAccount::run_helper, accounts[i]);
  }
  
  // wait for all threads (accounts) to die.
  for(int i = 0; i< NUM_ACCOUNTS; i++){
    pthread_join(accounts[i]->thread, NULL);
  }	
  
  cout << endl << "End of the week." << endl;
  
  int Total_Balance = 0;
  // sum up all balances.
  for(int i = 0; i< NUM_ACCOUNTS; i++){
    Total_Balance += accounts[i]->Balance;
  }	
  
  checkResult(Total_Balance);
}		

void Account::Service(int id, int sum) {
  accounts[id]->Balance += sum;
  Bank_Total += sum;
}


void Account::checkResult(int Total_Balance) {
  // Give report.
  cout << "Bank records = " << Bank_Total << 
    ", accounts balance = " << Total_Balance << "." << endl;
  if (Bank_Total == Total_Balance) {
    cout << "Records match." << endl;
  } else {
    cerr << "ERROR: records don't match !!!" << endl;
    exit(-1);
  }
}
