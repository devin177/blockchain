#include <iostream>
#include <string>
#include "blockchain.h"
#include <stdio.h>
#include <secp256k1.h>
#include "wallet.h"

using namespace std;

int main () {
  Blockchain bchain = Blockchain();
  cout << bchain.GetSize() << endl;
  
  string line_buffer;
  cout << ">";
  while (getline(cin, line_buffer)) {
    if (!line_buffer.compare("addblock")) {
      bchain.AddBlock(bchain.GetLastHash(), bchain.GetLastBlock().GetTransactions());
      cout << bchain.GetSize() << endl;
    } else if (!line_buffer.compare("generateaddress")) {
      GenerateAddress();
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
