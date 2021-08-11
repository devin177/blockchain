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
  void WriteBlock(int index, int nonce) const;
 private:
  // The blockchain itself is a vector of blocks. Will change this to something
  // to do with reading the "block.dat" files
  vector<unique_ptr<Block>> BChain;
  // Difficulty of mining last block
  uint32_t nbits;
  // Transactions accumulated since the last block was verified
  vector<Transaction> newTx;
};

// Should add way to verify who is mining this block
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
  WriteBlock(GetSize(), nonce);
  newTx.clear();
}

Blockchain::Blockchain() {
  // Setting difficulty of the mining process. Might change to be dynamic
  nbits = 2;

  // First ever CBTx to me as a default
  newTx.push_back(Transaction("1EDPeMx726w18mj44m1ehoneySLCr4SFVR"));

  // Hash "0" because this is the start of the chain
  string prevhash;
  picosha2::hash256_hex_string(string("0"), prevhash);

  time_t time = std::time(nullptr);
  int nonce = ProofOfWork(0, prevhash, newTx, (to_string(time)), nbits);
  BChain.push_back(make_unique<Block>(0, prevhash, newTx, stoi(to_string(time)), 2, nonce));
  // Write the newly created block to memory
  WriteBlock(GetSize(), nonce);
  // Allow room for new transactions
  newTx.clear();
}

// Write the latest block and all its transactions to a file
// Will be called block[index].dat
/* Format of Block ~ https://learnmeabitcoin.com/technical/blkdat
*/
void Blockchain::WriteBlock(int index, int nonce) const {
  string filename = "block";
  filename += to_string(index) += ".dat";
  ofstream block_file;
  block_file.open(filename, ios::out | ios::binary);
  if (!block_file) {
    cout << "error" << endl;
    return;
  }

  // Setting up places in memory for the parts of our block
  // Start of block data
  char magic_nums[4];
  magic_nums[0] = 0xf9;
  magic_nums[1] = 0xbe;
  magic_nums[2] = 0xb4;
  magic_nums[3] = 0xd9;
  block_file.write(magic_nums, 4);

  // block_file.write(size, however big the size of the incoming block is)

  // 64 byte Previous Hash
  string prev_hash = GetLastHash();
  const char* prev_buff = prev_hash.c_str();
  block_file.write(prev_buff, 64);

  // Merkle Root TBD size. I'm making my own convention

  // 4 byte time
  uint32_t time = GetLastBlock().GetTime();
  block_file.write((char*)&time, 4);

  // 4 bytes of difficulty bits
  block_file.write((char*)&nbits, 4);

  // 4 bytes of nonce
  block_file.write((char*)&nonce, 4);

  // 2 byte number of transactions
  int size = newTx.size();
  block_file.write((char*)&size, 2);

  // Transaction Data
  for (int i = 0; i < size; ++i) {
    // 2 byte number of inputs
    int num_in = newTx[i].vin.size();
    block_file.write((char*)&num_in, 2);
    // Input, not there temporarily

    // 2 byte number of outputs
    int num_out = newTx[i].vout.size();
    block_file.write((char*)&num_out, 2);

    // Outputs
    // for each output
    // 8 byte amount of devcoin
    int64_t value = newTx[i].vout[i].Amount;
    block_file.write((char*)&value, 8);
    // 34 byte address
    string address = newTx[i].vout[i].Address;
    const char* address_buff = address.c_str();
    block_file.write(address_buff, 34);
  }

  block_file.close();
  // ifstream read_file;
  // read_file.open(filename, ios::in | ios::binary);
  // char* buffer = (char*)malloc(68);
  // read_file.read(buffer, 68);
  // cout << buffer << endl;
  // read_file.close();
}
#endif
