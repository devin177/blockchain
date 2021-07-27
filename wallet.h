#ifndef WALLET_H
#define WALLET_H

#include <fcntl.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
// stuff from tutorial
#include <secp256k1.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>

// calling an unsigned char a byte
typedef unsigned char byte;

using namespace std;

static secp256k1_context *ctx = NULL;

class Wallet {
 public:
  Wallet() = default;
};

/* See https://en.wikipedia.org/wiki/Positional_notation#Base_conversion */
char* base58(byte *s, int s_size, char *out, int out_size) {
  static const char *base_chars = "123456789"
    "ABCDEFGHJKLMNPQRSTUVWXYZ"
    "abcdefghijkmnopqrstuvwxyz";

  byte s_cp[s_size];
  memcpy(s_cp, s, s_size);

  int c, i, n;

  out[n = out_size] = 0;
  while (n--) {
    for (c = i = 0; i < s_size; i++) {
      c = c * 256 + s_cp[i];
      s_cp[i] = c / 58;
      c %= 58;
    }
    out[n] = base_chars[c];
  }

  return out;
}

void GeneratePrivKey() {
  ctx = secp256k1_context_create(
	SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);

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

  if (!secp256k1_ec_seckey_verify(ctx, seckey)) {
	  printf("Invalid secret key\n");
    // error for invalid
  }

  // Use elliptic curve to generate pubkey
  secp256k1_pubkey pubkey;
  int temp = secp256k1_ec_pubkey_create(ctx, &pubkey, seckey);
  if (temp == 0) {
    ;
  }

  size_t pk_len = 65;
  unsigned char pk_bytes[34];

  /* Serialize Public Key */
  secp256k1_ec_pubkey_serialize(
    ctx,
    pk_bytes,
    &pk_len,
    &pubkey,
    SECP256K1_EC_UNCOMPRESSED
    );

  // Turn public key(in bytes) to bitcoin address
  // char pubaddress[34];
  byte s[65];
  byte rmd[5 + RIPEMD160_DIGEST_LENGTH];

  // Copy public key into temp var s
  for (int j = 0; j < 65; j++) {
	  s[j] = pk_bytes[j];
  }

  // 1. Take SHA256 hash of pubkey
  // 2. Take RIPEMD160 hash of ^
  // 3. Add a version byte in front (lets say 0x00)
  /* Set 0x00 byte for main net */
  rmd[0] = 0;
  RIPEMD160(SHA256(s, 65, 0), SHA256_DIGEST_LENGTH, rmd + 1);

  // 4. Create checksum by SHA256 hashing twice
  SHA256(SHA256(rmd, 21, 0), SHA256_DIGEST_LENGTH, 0);

  // 4.5. We only care about the last 4 bytes of the checksum, add them to the end
  memcpy(rmd + 21, SHA256(SHA256(rmd, 21, 0), SHA256_DIGEST_LENGTH, 0), 4);

  // 5. Store our Address in a char[34]
  // convert from bytes to base 58 string
  char address[34];
  base58(rmd, 25, address, 34);

  // leading 1's in base 58 don't count, so remove them
    /* Count the number of extra 1s at the beginning of the address */
  int k;
  for (k = 1; address[k] == '1'; k++);

  /* Count the number of extra leading 0x00 bytes */
  int n;
  for (n = 1; rmd[n] == 0x00; n++);

  /* Remove k-n leading 1's from the address */
  memmove(address, address + (k-n), 34-(k-n));
  address[34-(k-n)] = '\0';

  printf("Address: %s\n", address);

  // checksum
  byte tempadd[21];
  for (int i = 0; i < 21; ++i) {
    tempadd[i] = address[i];
  }

  SHA256(SHA256(tempadd, 21, 0), SHA256_DIGEST_LENGTH, 0);

  printf("Checksum: %s\n", tempadd);
}

#endif
