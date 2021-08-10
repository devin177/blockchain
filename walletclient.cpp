#include <iostream>
#include <string>
#include "blockchain.h"
#include <stdio.h>
#include <secp256k1.h>
#include "wallet.h"
#include <sstream>

using namespace std;

int main () {
  Blockchain bchain = Blockchain();
  
  string line_buffer;
  string cmd_buff;
  cout << ">";
  while (getline(cin, line_buffer)) {
    stringstream line_stream(line_buffer);
    line_stream >> cmd_buff;
    if (!cmd_buff.compare("addblock")) {
      bchain.AddBlock(bchain.GetLastHash());
    } else if (!cmd_buff.compare("generatewallet")) {
      GenerateWalletFile();
    } else if (!cmd_buff.compare("hashseed")){
      line_stream >> cmd_buff;
      HashPrivSeed(cmd_buff);
    } else {
      cout << "Closing program" << endl;
      break;
    }
    cout << ">";
  }

  return 0;
}

// Add transactions to the blocks
// First one to add: Coinbase transaction ~ the distribution of reward coins
