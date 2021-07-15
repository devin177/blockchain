#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

class Wallet {
 public:
  Wallet() = default;
};

void GeneratePrivKey() {
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
  printf("\n");
}

#endif
