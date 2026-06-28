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

static VirtualBankSystem initializeBankSystem() {
  VirtualBankSystem bank_service;

  bank_service.addCard("12345678", "0000", {"account_1", "account_2"});
  bank_service.setBalance("account_1", 100);
  bank_service.setBalance("account_2", 500);

  bank_service.addCard("01020304", "1234", {"account_3"});
  bank_service.setBalance("account_3", 800);
  return bank_service;
}

static VirtualCashSystem initializeCashSystem() {
  VirtualCashSystem cash_bin;

  cash_bin.insertCash(600);

  return cash_bin;
}

void testWithDrawInsufficientFunds() {
  VirtualBankSystem bank_service = initializeBankSystem();
  VirtualCashSystem cash_bin = initializeCashSystem();
  ATMController atm(bank_service, cash_bin);

  std::cout << "[1] Test account insufficient funds case." << std::endl;

  try {
    atm.insertCard("12345678");
    atm.enterPin("0000");
    atm.selectAccount("account_1");
    atm.withdraw(200);
  } catch (std::runtime_error& e) { std::cout << e.what() << std::endl; } // pass
}

void testWrongPinNumber() {
  VirtualBankSystem bank_service = initializeBankSystem();
  VirtualCashSystem cash_bin = initializeCashSystem();
  ATMController atm(bank_service, cash_bin);

  std::cout << "[2] Test wrong pin number case." << std::endl;
  try {
    atm.insertCard("01020304");
    atm.enterPin("0000");
  } catch (std::runtime_error& e) { std::cout << e.what() << std::endl; } // pass
}

void testThereIsNoAccount() {
  VirtualBankSystem bank_service = initializeBankSystem();
  VirtualCashSystem cash_bin = initializeCashSystem();
  ATMController atm(bank_service, cash_bin);

  std::cout << "[3] Test wrong account select case." << std::endl;
  try {
    atm.insertCard("01020304");
    atm.enterPin("1234");
    atm.selectAccount("account_1");
  } catch (std::runtime_error& e) { std::cout << e.what() << std::endl; } // pass
}

void testMinusDollar() {
  VirtualBankSystem bank_service = initializeBankSystem();
  VirtualCashSystem cash_bin = initializeCashSystem();
  ATMController atm(bank_service, cash_bin);

  std::cout << "[4] Test minus dollar case." << std::endl;
  try {
    atm.insertCard("12345678");
    atm.enterPin("0000");
    atm.selectAccount("account_1");
    atm.deposit(-10);
  } catch (std::runtime_error& e) { std::cout << e.what() << std::endl; } // pass
}

void testCashInsufficientFunds() {
  VirtualBankSystem bank_service = initializeBankSystem();
  VirtualCashSystem cash_bin = initializeCashSystem();
  ATMController atm(bank_service, cash_bin);

  std::cout << "[5] Test cash insufficient funds case." << std::endl;
  try {
    atm.insertCard("01020304");
    atm.enterPin("1234");
    atm.selectAccount("account_3");
    atm.deposit(150);
    atm.withdraw(900);
  } catch (std::runtime_error& e) { std::cout << e.what() << std::endl; } // pass
}

int main() {
  testWithDrawInsufficientFunds();
  testWrongPinNumber();
  testThereIsNoAccount();
  testMinusDollar();
  testCashInsufficientFunds();

  std::cout << " === Bank System Test Finished === " << std::endl;
  return 0;
}