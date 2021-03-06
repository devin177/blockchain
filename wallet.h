#ifndef WALLET_H
#define WALLET_H

#include <fcntl.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
// Imports for turning privkey to address
#include <secp256k1.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include "base58.h"
#include "hex.h"
#include "constants.h"

// calling an unsigned char a byte
typedef unsigned char byte;

using namespace std;

static secp256k1_context *ctx = NULL;

class Wallet {
 public:
  Wallet() = default;
};

/*Create and write into a new file: "wallet.dat"
  This will delete a previous wallet.dat
  Writes a new private key and wallet address
*/
void GenerateWalletFile() {
  ctx = secp256k1_context_create(
	SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);

  // wallet.dat apparently not encrypted by default
  FILE* wallet_file;
  wallet_file = fopen("wallet.dat", "w");

  // Private keys are 256 bits = 32 bytes
  unsigned char privkey[32];

  /* Load private key (seckey) from random bytes */
  FILE *frand = fopen("/dev/urandom", "r");
  fread(privkey, 32, 1, frand);
  fclose(frand);

  /* Loop through and print each byte of the private key, */
  for(int i=0; i<32; i++) {
    fprintf(wallet_file, "%02X", privkey[i]);
  }
  fprintf(wallet_file, "\n");

  if (!secp256k1_ec_seckey_verify(ctx, privkey)) {
	  printf("Invalid secret key\n");
    return;
  }

  // Generate a pubkey
  secp256k1_pubkey pubkey;
  int temp = secp256k1_ec_pubkey_create(ctx, &pubkey, privkey);

  // error check
  if (temp == 0) {
    cout << "Invalid Public Key. Try Again";
    return;
  }

  // UNCOMPRESSED bitcoin public keys are 65 bytes, the first of which is 0x04
  size_t pk_len = 65;
  unsigned char pk_bytes[65];

  /* Serialize Public Key */
  secp256k1_ec_pubkey_serialize(
    ctx,
    pk_bytes,
    &pk_len,
    &pubkey,
    SECP256K1_EC_UNCOMPRESSED
    );

  // Turn public key(in bytes) to bitcoin address
  byte dupe_pubkey[65];
  // RipeMD hash will be 20, 1 for version byte, 4 for checksum
  byte rmd[5 + RIPEMD160_DIGEST_LENGTH];

  // Copy public key into temp var s
  for (int j = 0; j < 65; j++) {
	  dupe_pubkey[j] = pk_bytes[j];
  }

  // 1. Take SHA256 hash of pubkey
  // 2. Take RIPEMD160 hash of ^
  // 3. Add a version byte in front (lets say 0x00)
  /* Set 0x00 byte for main net */
  rmd[0] = 0;
  RIPEMD160(SHA256(dupe_pubkey, 65, 0), SHA256_DIGEST_LENGTH, rmd + 1);

  // 4. Create checksum by SHA256 hashing the VERSION_BYTE+RIPEMD_HASH
  // 4.5. Append the first 4 bytes of doublehash to the end of original RIPEMD
  memcpy(rmd + 21, SHA256(SHA256(rmd, 21, 0), SHA256_DIGEST_LENGTH, 0), 4);

  // 5. Convert from bytes to base 58 string
  string address = EncodeBase58(rmd, rmd+25);
  const char* address_buff = address.c_str();
  fprintf(wallet_file, "%s\n", address_buff);
  fclose(wallet_file);
}

// Parse through a single block, and find transactions for your wallet
void ParseBlock(string block_name, string pub_address) {
  // Open block file to begin reading
  fstream block_file;
  block_file.open(block_name, fstream::in);
  if (!block_file.is_open()) {
    cout << "File error" << endl;
    return;
  }

  // If i were to keep this byte stream reading on all the time
  // I could probably do a while loop looking for the 4 magic bytes?

  // First four bytes SHOULD be 0xf94bebd9
  byte message_head[4];
  block_file.read((char*)message_head, 4);
  for (int i = 0; i < 4; ++i) {
    printf("%02x", message_head[i]);
  }
  cout << endl;
  // Error check for magic bytes
  if (memcmp(magic, message_head, 4)) {
    cout << "Error with beginning of block" << endl;
    return;
  }

  // next 64 bytes is the hash of the previous block
  byte block_hash[64];
  block_file.read((char*)block_hash, 64);
  for (int i = 0; i < 64; ++i) {
    printf("%c", block_hash[i]);
  }
  cout << endl;

  uint32_t time[4];
  block_file.read((char*)time, 4);
  for (int i = 0; i < 1; ++i) {
    printf("%u", time[i]);
  }
  cout << endl;


  uint32_t nbits[4];
  block_file.read((char*)nbits, 4);
  for (int i = 0; i < 4; ++i) {
    printf("%u", nbits[i]);
  }
    cout << endl;


  uint32_t nonce[4];
  block_file.read((char*)nonce, 4);
  for (int i = 0; i < 4; ++i) {
    printf("%i", nonce[i]);
  }
    cout << endl;


  // Number of transactions
  int size[2];
  block_file.read((char*)size, 2);
  for (int i = 0; i < 2; ++i) {
    printf("%i", size[i]);
  }
    cout << endl;


  // start of inputs
  int num_in[2];
  block_file.read((char*)num_in, 2);
  for (int i = 0; i < 2; ++i) {
    printf("%i", num_in[i]);
  }
    cout << endl;


  // To Do
  // Loop similarly to blockchain writeblock, by transaction, then by io

  // To Do
  // inputs

  // start of outputs
  int num_out[2];
  block_file.read((char*)num_out, 2);
  for (int i = 0; i < 2; ++i) {
    printf("%i", num_out[i]);
  }
    cout << endl;

}

// Given a seeded private key, find its public address
void HashPrivSeed(string privkey){
  // Turn 64 bit string to 32 bit privkey, then do the hashing
  byte seed[32];
  string string_val = hex_to_string(privkey);
  for (int i = 0; i < 32; ++i) {
    seed[i] = string_val[i];
  }
  ctx = secp256k1_context_create(
	  SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);

    if (!secp256k1_ec_seckey_verify(ctx, seed)) {
	  printf("Invalid secret key\n");
    return;
  }

  // Generate a pubkey
  secp256k1_pubkey pubkey;
  int temp = secp256k1_ec_pubkey_create(ctx, &pubkey, seed);

    // error check
  if (temp == 0) {
    cout << "Invalid Public Key. Try Again";
    return;
  }

  size_t pk_len = 65;
  unsigned char pk_bytes[65];

  /* Serialize Public Key */
  secp256k1_ec_pubkey_serialize(
    ctx,
    pk_bytes,
    &pk_len,
    &pubkey,
    SECP256K1_EC_UNCOMPRESSED
    );

  // Turn public key(in bytes) to bitcoin address
  byte dupe_pubkey[65];
  // RipeMD hash will be 20, 1 for version byte, 4 for checksum
  byte rmd[5 + RIPEMD160_DIGEST_LENGTH];

  // Copy public key into temp var s
  for (int j = 0; j < 65; j++) {
	  dupe_pubkey[j] = pk_bytes[j];
  }

  // 1. Take SHA256 hash of pubkey
  // 2. Take RIPEMD160 hash of ^
  // 3. Add a version byte in front (lets say 0x00)
  /* Set 0x00 byte for main net */
  rmd[0] = 0;
  RIPEMD160(SHA256(dupe_pubkey, 65, 0), SHA256_DIGEST_LENGTH, rmd + 1);

  // 4. Create checksum by SHA256 hashing the VERSION_BYTE+RIPEMD_HASH
  // 4.5. Append the first 4 bytes of doublehash to the end of original RIPEMD
  memcpy(rmd + 21, SHA256(SHA256(rmd, 21, 0), SHA256_DIGEST_LENGTH, 0), 4);

  // 5. Convert from bytes to base 58 string
  string address = EncodeBase58(rmd, rmd+25);
  cout << address << endl;
}
#endif
