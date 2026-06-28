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
    void selectAccount();
    void ejectCard();

    // Back function set-up
    void getBalance();
    void deposit();
    void withdraw();

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