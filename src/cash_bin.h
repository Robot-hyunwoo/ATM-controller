#ifndef CASH_BIN_H
#define CASH_BIN_H

#include <iostream>
#include <string>
#include <vector>

/*
 * This is a virtual API for cash bin system.
 */

class CashBin {
  public:
  virtual ~CashBin() = default;

  virtual int checkCash() = 0;
  virtual void insertCash(int dollars) = 0;
  virtual void extractCash(int dollars) = 0;
};

#endif
