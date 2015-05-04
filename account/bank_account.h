class BankAccount {
  public:
    int Balance;
    int Account_Id;
	BankAccount(void);
	static const int MAX_SUM = 300;
    
    void Action();
    void* run(void *);
};
