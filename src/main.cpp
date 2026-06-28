#include "atm_controller.h"
#include "bank_service.h"
#include "cash_bin.h"

#include <iostream>
#include <string>
#include <vector>

class VirtualBackSystem : public BankService {
  public:
    bool validatePinNumber(const std::string& current_card_number,
                          const std::string& pin_number) override { return true; } // for test
    std::vector<std::string> getAccountsDB(const std::string& current_card_number) override {
      std::vector<std::string> accounts;
      return accounts;
    }
    int getBalance(const std::string &current_account) override { return 0; };
    void deposit(const std::string &current_account, int dollars) override { }; // for test
    void withdraw(const std::string &current_account, int dollars) override { }; // for test
};

class VirtualCashSystem : public CashBin {
  public:
    bool checkCash(int dollars) override { return true; /* check cash in bin */ }
    void insertCash(int dollars) override { /* insert cash to bin */ }
    void extractCash(int dollars) override { /* extract cash from bin */ }
};

int main() {
  VirtualBackSystem bank_service;
  VirtualCashSystem cash_bin;

  ATMController atm(bank_service, cash_bin);

  atm.insertCard("123456");
  atm.enterPin("1234");
  atm.getAccounts();
  atm.selectAccount("card_1");
  atm.deposit(120);
  atm.withdraw(50);
  atm.ejectCard();

  return 0;
}