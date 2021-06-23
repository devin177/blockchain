#ifndef HASH_H
#define HASH_h
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "transaction.h"
#include "PicoSHA2/picosha2.h"
using namespace std;

// Return a nonce that works with the given data to find a suitable hash
int ProofOfWork(int index, string prevhash,
  vector<Transaction> tx, string time, uint32_t nbits) {
  // Hash the header with a nonces until one satisfies the nbits req
  stringstream threshold;
  for (uint32_t i = 0; i < nbits; ++i) {
    threshold << "0";
  }
  string header;
  uint32_t nonce = 0;
  string hashed_header;
  for (; nonce < UINT32_MAX; ++nonce) {
    header = to_string(index) + prevhash + (time) + to_string(nbits) + to_string(nonce);
    picosha2::hash256_hex_string(header, hashed_header);
    if (hashed_header.substr(0,2) == threshold.str()) {
      break;
    }
  }
  
  cout << hashed_header << endl;
  return nonce;
}
#endif
