#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <memory>
#include "block.h"

using namespace std;

class Blockchain {
 public:
  Blockchain();

  Block GetBlock(int index);

  void AddBlock(int index, string prevhash,
    vector<Transaction> tx, uint32_t time, uint32_t nbits, uint32_t nonce);

  Block GetLastBlock() const;
 private:
  vector<unique_ptr<Block>> BChain;
};

void Blockchain::AddBlock(int index, string prevhash,
  vector<Transaction> tx, uint32_t time, uint32_t nbits, uint32_t nonce) {
  
}

#endif
