#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include "block.h"
#include "hash.h"
#include "transaction.h"

using namespace std;

class Blockchain {
 public:
  // constructor
  Blockchain();

  // Returns how many blocks are on the BChain
  int GetSize() {return BChain.size();}

  // Return the block of a certain index
  Block GetBlock(int index) {return *(BChain[index]);}

  // add a new block to the BChain
  void AddBlock(string prevhash, vector<Transaction> tx);

  // Return just the last block in the BChain
  Block GetLastBlock() const {return *(BChain[BChain.size()-1]);}

  string GetLastHash() const {return GetLastBlock().GetHash();}

  // Create a coinbase transaction, and give it to the account that mined
  void CoinbaseTx();
 private:
  vector<unique_ptr<Block>> BChain;
  uint32_t nbits;
  vector<Transaction> newTx;
};

void Blockchain::AddBlock(string prevhash, vector<Transaction> tx) {
  int index = GetSize();

  // Timing. Should be at least 10 seconds between each new block
  time_t time = std::time(nullptr);

  /*if (stoi(to_string(time)) - GetLastBlock().GetTime() < 2) {
    cout << "Time since last block added too short. Please try again later." << endl;
    return;
  }*/

  // The nonce and hash of the current block
  int nonce = ProofOfWork(index, prevhash, tx, to_string(time), nbits);
  BChain.push_back(make_unique<Block>(index, prevhash, tx, stoi(to_string(time)), nbits, nonce));
}

Blockchain::Blockchain() {
  nbits = 2;

  vector<Transaction> tx;
  // tx.push_back(Transaction(address));

  // Hash "0" because this is the start of the chain
  string prevhash;
  picosha2::hash256_hex_string(string("0"), prevhash);
  time_t time = std::time(nullptr);
  int nonce = ProofOfWork(0, prevhash, tx, (to_string(time)), nbits); 
  cout << nonce << endl;
  BChain.push_back(make_unique<Block>(0, prevhash, tx, stoi(to_string(time)), 2, nonce));
}

void Blockchain::CoinbaseTx() {

}
#endif
