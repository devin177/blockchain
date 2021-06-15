#include <functional>
#include <string>
#include <sstream>
#include "block.h"
#include "sha256.h"

Block::Block(uint32_t IndexIn, const string &DataIn) : Index(IndexIn), Data(DataIn) {
  Nonce = -1;
  Time = time (nullptr);
}

string Block::GetHash() {
  return Hash;
}

void Block::MineBlock(uint32_t Difficulty) {
  char cstr[Difficulty + 1];
  for (uint32_t i = 0; i < Difficulty; ++i) {
    cstr[i] = '0';
  }
  cstr[Difficulty] = '\0';

  string str(cstr);

  do {
    Nonce++;
    Hash = CalculateHash();
  } while (Hash.substr(0, Difficulty) != str);

  cout << "Block Mined: " << Hash << endl;
}

string Block::CalculateHash() const {
  stringstream ss;
  ss << Index << Time << Data << Nonce << PrevHash;
  return sha256(ss.str());
}
