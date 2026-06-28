#include "atm_controller.h"
#include "bank_service.h"
#include "cash_bin.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>

class VirtualBankSystem : public BankService {
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
      const auto iter = card_pin_.find(current_card_number);
      return (iter != card_pin_.end() && iter->second == pin_number);
    }
    std::vector<std::string> getAccountsDB(const std::string& current_card_number) override {
      const auto iter = card_accounts_.find(current_card_number);

      std::vector<std::string> accounts;
      if (iter != card_accounts_.end()) {accounts = iter->second;}
      return accounts;
    }
    int getBalance(const std::string &current_account) override {
      return account_balance_[current_account];
    };
    void deposit(const std::string &current_account, const int dollars) override {
      account_balance_[current_account] += dollars;
    };
    void withdraw(const std::string &current_account, const int dollars) override {
      account_balance_[current_account] -= dollars;
    };

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
    int checkCash() override {
      return cash_in_bin_;
    }
    void insertCash(const int dollars) override {
      cash_in_bin_ += dollars;
    }
    void extractCash(const int dollars) override {
      cash_in_bin_ -= dollars;
    }
  private:
    /* ------------------ for demo ---------------- */
    int cash_in_bin_ = 0;
    /* -------------------------------------------- */
};

int main() {
  VirtualBankSystem bank_service;
  VirtualCashSystem cash_bin;

  // Make test case for demo
  bank_service.addCard("12345678", "0000", {"account_1", "account_2"});
  bank_service.setBalance("account_1", 100);
  bank_service.setBalance("account_2", 500);

  bank_service.addCard("01020304", "1234", {"account_3"});
  bank_service.setBalance("account_3", 120);

  cash_bin.insertCash(600);

  ATMController atm(bank_service, cash_bin);

  try {
    atm.insertCard("12345678");
    std::cout << "[1] Card is inserted." << std::endl;

    atm.enterPin("0000");
    std::cout << "[2] PIN number is accepted." << std::endl;

    atm.getAccounts();
    std::cout << "[3] Check account in this card..." << std::endl;

    atm.selectAccount("account_1");
    std::cout << "[4] Account is selected." << std::endl;

    atm.deposit(100);
    std::cout << "[5] Deposited." << std::endl;

    atm.withdraw(150);
    std::cout << "[6] Withdraw." << std::endl;

    atm.ejectCard();
    std::cout << "[7] Take your card." << std::endl;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << " === Bank System Demo Finished === " << std::endl;
  return 0;
}