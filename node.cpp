#include <iostream>
#include <string>
#include "blockchain.h"
#include <stdio.h>
#include <secp256k1.h>

using namespace std;

int main () {
  Blockchain bchain = Blockchain();
  cout << bchain.GetSize() << endl;
  
  string line_buffer;
  /*while (getline(cin, line_buffer)) {
    if (!line_buffer.compare("addblock")) {
      bchain.AddBlock(bchain.GetLastHash(), bchain.GetLastBlock().GetTransactions());
      cout << bchain.GetSize() << endl;
    }
  }*/

  // static secp256k1_context* ctx = NULL;
  //ctx = secp256k1_context_create(
  // SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
  /* Declare the private variable as a 32 byte unsigned char */
  unsigned char seckey[32];

  /* Load private key (seckey) from random bytes */
  FILE *frand = fopen("/dev/urandom", "r");

  /* Read 32 bytes from frand */
  fread(seckey, 32, 1, frand);

  /* Close the file */
  fclose(frand);

  /* Loop through and print each byte of the private key, */
  printf("Private Key: ");
  for(int i=0; i<32; i++) {
      printf("%02X", seckey[i]);
    }
  return 0;
}

// Add transactions to the blocks
// First one to add: Coinbase transaction ~ the distribution of reward coins
