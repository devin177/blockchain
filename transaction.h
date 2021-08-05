#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include <vector>

using namespace std;

// individual inputs
class TxIn {
 public:
  // Identify the output we are trying to spend
  string TxId;
  uint32_t index;

  // signature script that will satisfy pubkey script

};

// individual outputs
// This is the record that makes up people's wallets
// Transactions are stored in the UTXO set?
class TxOut {
 public:
  TxOut(int64_t amount, string address): Amount(amount),
    Address(address){
      ;
    };

  // implied index from location in vector
  int64_t Amount;

  // Conditional pubkey script
  // For now, I will just put a address that I will check is the same
  string Address;
  void spend() {Spent = true;}
 private:
  bool Spent = false;
};

class Transaction {
 public:
  // Normal transaction
  Transaction(vector<TxIn> inputs, vector<TxOut> outputs);

  // Coinbase transaction to one miner
  Transaction(string address) {
    TxOut CBTx(50, address);
    vout.push_back(CBTx);
  }

  // Hash of the TX -> will be used to find merkle root
  string TXHash;

  // Version/convention of transaction
  // int32_t version;
  // Array of inputs
  vector<TxIn> vin;

  // Array of outputs
  vector<TxOut> vout;
  /* no partial spending?
  * Add up your incoming tx - outgoing tx for balance
  * For partials, send some?
  */
};

#endif
