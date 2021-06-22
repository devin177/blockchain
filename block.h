#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>
#include <iostream>
#include <string>
#include "transaction.h"

using namespace std;

class Block {
 public:
  Block (int IndexIn);

  // return the hash of this block
  string GetHash();

  // return the hash of previous block header

  // Return the index
  int GetIndex();


 private:
  // index is a temporary field
  // This will be removed when I begin to write the bchain to file instead
  // of it being a vector
  // its the height of the blockchain
  int Index;
  string PrevHash;
  // Also temporary until I figure out how transactions work
  vector<Transaction> TX;
  // string MerkleRootHash;
  uint32_t Time;
  uint32_t nBits;
  uint32_t Nonce;
};
#endif
