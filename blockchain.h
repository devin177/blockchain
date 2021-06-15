#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <iostream>
#include <vector>
#include "block.h"

using namespace std;

class Blockchain {
 public:
  Blockchain();

  void AddBlock(Block New);

 private:
  uint32_t Difficulty;
  vector<Block> Chain;

  Block GetLastBlock() const;
};

#endif
