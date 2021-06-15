#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>
#include <iostream>

using namespace std;

class Block {
 public:
  string PrevHash;

  Block (uint32_t IndexIn, const string &DataIn);

  string GetHash();

  void MineBlock(uint32_t Difficulty);

 private:
  uint32_t Index;
  int64_t Nonce;
  string Data;
  string Hash;
  time_t Time;

  string CalculateHash() const;
};



#endif
