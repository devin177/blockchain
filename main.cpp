#include "blockchain.h"
#include <openssl/sha.h>
#include <typeinfo>

int main () {
  Blockchain bChain = Blockchain();

  cout << "Mining Block 1..." << endl;
  bChain.AddBlock(Block(1, "Block 1 Data"));

  const unsigned char temp[] = "1";
  const unsigned char temp2[] = "1";
  unsigned char hash[SHA256_DIGEST_LENGTH];
  unsigned char hash2[SHA256_DIGEST_LENGTH];

  SHA256(temp, sizeof(temp), hash);
  SHA256(temp2, sizeof(temp2), hash2);
  
  cout << boolalpha << (*hash == *hash2) << endl;

  return 0;
}
