#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>

using namespace std;

class Transaction {
 public:
  string TXHash;
  Transaction();
  /* no partial spending?
  * Add up your incoming tx - outgoing tx for balance
  * For partials, send some?
  */
};

#endif
