#include "atm_controller.h"

#include <iostream>
#include <string>
#include <vector>

int main() {
  ATMController atm;

  atm.insertCard();
  atm.enterPin();
  atm.getAccounts();
  atm.selectAccount();
  atm.deposit();
  atm.withdraw();
  atm.ejectCard();

  return 0;
}