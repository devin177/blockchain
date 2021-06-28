#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include <vector>

using namespace std;

class TxIn {

};

class TxOut {

};

class Transaction {
 public:
  // Constructor
  Transaction();

  // Hash of the TX -> will be used to find merkle root
  string TXHash;

  // Version/convention of transaction
  int32_t version;
  // Array of inputs
  vector<TxIn> in;

  // Array of outputs
  vector<TxOut> out;
  /* no partial spending?
  * Add up your incoming tx - outgoing tx for balance
  * For partials, send some?
  */
};

#endif
