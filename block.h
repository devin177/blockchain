#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>
#include <iostream>
#include <string>
#include <sstream>
#include "transaction.h"

/* The header for my blockchain will consist of
  * Index
  * PrevHash
  * Transaction - merkle root in the future
  * Time
  * nBits
  * Nonce 
*/

using namespace std;

class Block {
 public:
  // Constructor
  Block (int Index, string PrevHash, vector<Transaction> TX,
    uint32_t Time, uint32_t nBits, uint32_t Nonce): Index(Index),
      PrevHash(PrevHash), TX(TX), Time(Time), nBits(nBits), Nonce(Nonce){
      ;
    };

  // return the header of this block
  string GetHeader();

  // return the hash of previous block header
  string GetPrevHash() {return PrevHash;}

  // Return the index
  int GetIndex() {return Index;}

  int GetTime() {return Time;}

  // Return the list of transactions for this block
  vector<Transaction> GetTransactions() {return TX;}
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

string Block::GetHeader() {
  stringstream ss;
  ss << Index << PrevHash /*<< TX*/ << Time << nBits << Nonce;
  return ss.str();
}
#endif
