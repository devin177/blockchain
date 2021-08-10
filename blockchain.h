#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <iostream>
#include <fstream>
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
  int GetSize() const {return BChain.size();}

  // Return the block of a certain index
  Block GetBlock(int index) {return *(BChain[index]);}

  // Return just the last block in the BChain
  Block GetLastBlock() const {return *(BChain[BChain.size()-1]);}

  // Get the hash of the last block
  string GetLastHash() const {return GetLastBlock().GetHash();}

  // add a new block to the BChain
  void AddBlock(string prevhash);

  // Write to memory the latest block
  void WriteBlock(int index) const;
 private:
  // The blockchain itself is a vector of blocks. Will change this to something
  // to do with reading the "block.dat" files
  vector<unique_ptr<Block>> BChain;
  // Difficulty of mining last block
  uint32_t nbits;
  // Transactions accumulated since the last block was verified
  vector<Transaction> newTx;
};

void Blockchain::AddBlock(string prevhash) {
  int index = GetSize();

  // Timing. Should be at least 10 seconds between each new block
  time_t time = std::time(nullptr);

  /*if (stoi(to_string(time)) - GetLastBlock().GetTime() < 2) {
    cout << "Time since last block added too short. Please try again later." << endl;
    return;
  }*/

  // The nonce and hash of the current block
  int nonce = ProofOfWork(index, prevhash, newTx, to_string(time), nbits);
  BChain.push_back(make_unique<Block>(index, prevhash, newTx, stoi(to_string(time)), nbits, nonce));
  WriteBlock(GetSize());
}

Blockchain::Blockchain() {
  // Setting difficulty of the mining process. Might change to be dynamic
  nbits = 2;

  vector<Transaction> tx;
  // CBTx to me as a default
  tx.push_back(Transaction("1EDPeMx726w18mj44m1ehoneySLCr4SFVR"));

  // Hash "0" because this is the start of the chain
  string prevhash;
  picosha2::hash256_hex_string(string("0"), prevhash);

  time_t time = std::time(nullptr);
  int nonce = ProofOfWork(0, prevhash, tx, (to_string(time)), nbits);
  BChain.push_back(make_unique<Block>(0, prevhash, tx, stoi(to_string(time)), 2, nonce));
  cout << GetLastBlock().GetTime() << endl;
  WriteBlock(GetSize());
}

// Write the latest block and all its transactions to a file
// Will be called block[index].dat
/* Format of Block ~ https://learnmeabitcoin.com/technical/blkdat
*/
void Blockchain::WriteBlock(int index) const {
  FILE* block_file;
  string filename = "block";
  filename += to_string(index) += ".dat";
  block_file = fopen(filename.c_str(), "w");
  fprintf(block_file, "%s", GetLastBlock().GetHeader().c_str());
  fclose(block_file);
}
#endif
