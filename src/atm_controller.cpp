#include "atm_controller.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

ATMController::ATMController(BankService& bank_service, CashBin& cash_bin)
  : bank_service_(bank_service), cash_bin_(cash_bin), state_(ATMState::IDLE) {}

ATMState ATMController::state() const {
  return state_;
}

void ATMController::insertCard(const std::string& card_number) {
  if (state_ != ATMState::IDLE) {
    throw std::runtime_error("ATM controller is not already.");
  }

  if (card_number.empty()) {
    throw std::runtime_error("Card number must not be empty.");
  }

  current_card_number_ = card_number;
  state_ = ATMState::PIN_WAITED;
}

void ATMController::enterPin(const std::string& pin_number) {
  if (state_ != ATMState::PIN_WAITED) {
    throw std::runtime_error("Please insert your card.");
  }

  // Bank service and Cash bin is Dummy. (Project)
  if (!bank_service_.validatePinNumber(current_card_number_, pin_number)) {
    throw std::runtime_error("Incorrect PIN number.");
  }
}

std::vector<std::string> ATMController::getAccounts() {
  std::vector<std::string> dummy_string;

  return dummy_string;
}

void ATMController::selectAccount() {

}

void ATMController::ejectCard() {

}

void ATMController::getBalance() {

}

void ATMController::deposit() {

}

void ATMController::withdraw() {

}
