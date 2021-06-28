#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include "block.h"
#include "hash.h"

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
  void AddBlock(int index, string prevhash,
    vector<Transaction> tx, uint32_t time, uint32_t nbits);

  // Return just the last block in the BChain
  Block GetLastBlock() const {return *(BChain[BChain.size()-1]);}
 private:
  vector<unique_ptr<Block>> BChain;
};

void Blockchain::AddBlock(int index, string prevhash,
  vector<Transaction> tx, uint32_t time, uint32_t nbits) {
  // Timing. Should be at least 10 seconds between each new block
  if (time - GetLastBlock().GetTime() < 10) {
    return;
  }

  // The nonce and hash of the current block
  int nonce = ProofOfWork(index, prevhash, tx, to_string(time), nbits);
  BChain.push_back(make_unique<Block>(index, prevhash, tx, time, nbits, nonce));
}

Blockchain::Blockchain() {
  vector<Transaction> tx;
  string prevhash;
  picosha2::hash256_hex_string(string("0"), prevhash);
  time_t time = std::time(nullptr);
  int nonce = ProofOfWork(0, prevhash, tx, (to_string(time)), 4); 
  cout << nonce << endl;
  BChain.push_back(make_unique<Block>(0, prevhash, tx, stoi(to_string(time)), 2, nonce));
}
#endif
