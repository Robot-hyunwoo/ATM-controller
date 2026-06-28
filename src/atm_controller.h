#ifndef ATM_CONTROLLER_H
#define ATM_CONTROLLER_H

#include "bank_service.h"
#include "cash_bin.h"

#include <string>
#include <vector>

enum class ATMState {
  IDLE,
  PIN_WAITED,
  ACCOUNT_WAITED,
  FUNCTION_WAITED
};

class ATMController {
  public:
    ATMController(BankService& bank_service, CashBin& cash_bin);

    // Card and account set-up
    void insertCard(const std::string& card_number);
    void enterPin(const std::string& pin_number);
    std::vector<std::string> getAccounts();
    void selectAccount(const std::string& account_id);
    void ejectCard();

    // Back function set-up
    int getBalance() const;
    void deposit(int dollars) const;
    void withdraw(int dollars) const;

    // State
    ATMState state() const;

  private:
    BankService& bank_service_;
    CashBin& cash_bin_;
    ATMState state_;
    std::string current_card_number_;
    std::string current_account_;
};

#endif