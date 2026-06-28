#ifndef BANK_SERVICE_H
#define BANK_SERVICE_H

#include <string>
#include <vector>

/*
 * This is a virtual API for bank service system.
 */

class BankService {
  public:
    virtual bool validatePinNumber(const std::string& current_card_number,
                            const std::string& pin_number) = 0;
};

#endif
