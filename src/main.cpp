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
};

class VirtualCashSystem : public CashBin {
  public:
    void dummyCash(int dollars) override { } // for test
};

int main() {
  VirtualBackSystem bank_service;
  VirtualCashSystem cash_bin;

  ATMController atm(bank_service, cash_bin);

  atm.insertCard("123456");
  atm.enterPin("1234");
  atm.getAccounts();
  atm.selectAccount();
  atm.deposit();
  atm.withdraw();
  atm.ejectCard();

  return 0;
}