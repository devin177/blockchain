#include "blockchain.h"

int main () {
  Blockchain bchain = Blockchain();
  cout << bchain.GetLastBlock().GetIndex() << endl;
  cout << bchain.GetLastBlock().GetPrevHash() << endl;
  cout << bchain.GetLastBlock().GetTime() << endl;
  cout << bchain.GetLastBlock().GetHeader() << endl;
  return 0;
}

// Add transactions to the blocks
// First one to add: Coinbase transaction ~ the distribution of reward coins
