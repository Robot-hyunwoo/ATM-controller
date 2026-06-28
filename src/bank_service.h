#ifndef BANK_SERVICE_H
#define BANK_SERVICE_H

#include <iostream>
#include <string>
#include <vector>

/*
 * This is a virtual API for bank service system.
 */

class BankService {
  public:
  virtual ~BankService() = default;

  virtual bool validatePinNumber(const std::string& current_card_number,
                                const std::string& pin_number) = 0;
    virtual std::vector<std::string> getAccountsDB(const std::string& current_card_number) = 0;
    virtual int getBalance(const std::string& current_account) = 0;
    virtual void deposit(const std::string& current_account, int dollars) = 0;
    virtual void withdraw(const std::string& current_account, int dollars) = 0;
};

#endif
