#ifndef CASH_BIN_H
#define CASH_BIN_H

#include <string>
#include <vector>

/*
 * This is a virtual API for cash bin system.
 */

class CashBin {
  public:
    virtual void dummyCash(int dollars) = 0;
};

#endif
