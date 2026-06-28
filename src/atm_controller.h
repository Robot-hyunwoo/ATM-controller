#ifndef ATM_CONTROLLER_H
#define ATM_CONTROLLER_H

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
    ATMController();

    // Card and account set-up
    void insertCard();
    void enterPin();
    std::vector<std::string> getAccounts();
    void selectAccount();
    void ejectCard();

    // Back function set-up
    void getBalance();
    void deposit();
    void withdraw();

    // State
    ATMState state();

  private:
};

#endif