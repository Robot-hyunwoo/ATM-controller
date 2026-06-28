#include "atm_controller.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
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

  std::cout << "Card is inserted." << std::endl;

  current_card_number_ = card_number;
  state_ = ATMState::PIN_WAITED;
}

void ATMController::enterPin(const std::string& pin_number) {
  if (state_ != ATMState::PIN_WAITED) {
    throw std::runtime_error("Please insert your card.");
  }

  // Bank service and Cash bin is virtual
  if (!bank_service_.validatePinNumber(current_card_number_, pin_number)) {
    throw std::runtime_error("Incorrect PIN number.");
  }

  std::cout << "PIN number is entered." << std::endl;

  state_ = ATMState::ACCOUNT_WAITED;
}

std::vector<std::string> ATMController::getAccounts() {
  std::vector<std::string> account;

  return account;
}

void ATMController::selectAccount(const std::string& account_id) {
  if (state_ != ATMState::ACCOUNT_WAITED) {
    throw std::runtime_error("Cannot be load your account.");
  }

  // load account by getAccounts and compare with selected account
  std::vector<std::string> accountsDB = bank_service_.getAccountsDB(current_card_number_);

  // Not found
  if (std::find(accountsDB.begin(), accountsDB.end(), account_id) == accountsDB.end()) {
    throw std::runtime_error("Selected account is not belong to this card.");
  }

  std::cout << "Find your account from card : " << current_card_number_ << std::endl;

  // Save the founded account id
  current_account_ = account_id;
  state_ = ATMState::FUNCTION_WAITED;
}

void ATMController::ejectCard() {

}

int ATMController::getBalance() const {
  if (state_ != ATMState::FUNCTION_WAITED) {
    throw std::runtime_error("Please select the account to check balance.");
  }

  return bank_service_.getBalance(current_card_number_);
}

void ATMController::deposit(int dollars) {
  if (state_ != ATMState::FUNCTION_WAITED) {
    throw std::runtime_error("Please select the account to deposit.");
  }

  if (dollars <= 0) {
    throw std::runtime_error("Dollars must be greater than 0.");
  }

  std::cout << "Deposit " << dollars << " will be inserted in " << current_account_ << std::endl;

  // Cash insert and update account
  cash_bin_.insertCash(dollars);
  bank_service_.deposit(current_account_, dollars);
}

void ATMController::withdraw(int dollars) {
  if (state_ != ATMState::FUNCTION_WAITED) {
    throw std::runtime_error("Please select the account to withdraw.");
  }

  if (dollars <= 0) {
    throw std::runtime_error("Dollars must be greater than 0.");
  }

  // Check balance
  if (bank_service_.getBalance(current_account_) < dollars) {
    throw std::runtime_error("Insufficient balance.");
  }

  // Check cash bin
  if (!cash_bin_.checkCash(dollars)) {
    throw std::runtime_error("ATM has insufficient cash.");
  }

  // Cash extract and update account
  bank_service_.withdraw(current_account_, dollars);
  cash_bin_.extractCash(dollars);
}
