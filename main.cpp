#include "blockchain.h"

int main () {
  Blockchain bChain = Blockchain();

  cout << "Mining Block 1..." << endl;
  bChain.AddBlock(Block(1, "Block 1 Data"));
  return 0;
}
