#include "atm_controller.h"
#include "bank_service.h"
#include "cash_bin.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>

class VirtualBackSystem : public BankService {
  public:
    /* ------------------ for demo ---------------- */
    void addCard(const std::string& card, const std::string& pin, const std::vector<std::string>& accounts) {
      card_pin_[card] = pin;
      card_accounts_[card] = accounts;
    }

    void setBalance(const std::string& account, const int& balance) {
      account_balance_[account] = balance;
    }

    /* -------------------------------------------- */

    bool validatePinNumber(const std::string& current_card_number,
                          const std::string& pin_number) override {
      std::map<std::string, std::string>::iterator iter = card_pin_.find(current_card_number);
      return (iter != card_pin_.end() && iter->second == pin_number);
    }
    std::vector<std::string> getAccountsDB(const std::string& current_card_number) override {
      std::vector<std::string> accounts;
      return accounts;
    }
    int getBalance(const std::string &current_account) override { return 0; };
    void deposit(const std::string &current_account, int dollars) override { }; // for test
    void withdraw(const std::string &current_account, int dollars) override { }; // for test

  private:
    /* ------------------ for demo ---------------- */
    // card, pin
    std::map<std::string, std::string> card_pin_;
    // card, accounts
    std::map<std::string, std::vector<std::string>> card_accounts_;
    // account, balance
    std::map<std::string, int> account_balance_;
    /* -------------------------------------------- */

};

class VirtualCashSystem : public CashBin {
  public:
    int checkCash() override { return 0; /* check cash in bin */ }
    void insertCash(int dollars) override { /* insert cash to bin */ }
    void extractCash(int dollars) override { /* extract cash from bin */ }
};

int main() {
  VirtualBackSystem bank_service;
  VirtualCashSystem cash_bin;

  // Make test case for demo
  bank_service.addCard("12345678", "0000", {"account_1", "account_2"});
  bank_service.setBalance("account_1", 100);
  bank_service.setBalance("account_2", 500);

  bank_service.addCard("01020304", "1234", {"account_3"});
  bank_service.setBalance("account_3", 120);

  cash_bin.insertCash(600);

  ATMController atm(bank_service, cash_bin);

  atm.insertCard("12345678");
  std::cout << "[1] Card is inserted." << std::endl;

  atm.enterPin("0000");
  std::cout << "[2] PIN number is accepted." << std::endl;

  atm.getAccounts();
  std::cout << "[3] Check account in this card..." << std::endl;

  atm.selectAccount("account_1");
  std::cout << "[4] Account is selected." << std::endl;

  atm.deposit(80);
  std::cout << "[5] Deposited." << std::endl;

  atm.withdraw(150);
  std::cout << "[6] Withdraw." << std::endl;

  atm.ejectCard();
  std::cout << "[7] Take your card." << std::endl;

  std::cout << " === Bank System Demo Finished === " << std::endl;
  return 0;
}