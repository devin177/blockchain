#include "blockchain.h"

Blockchain::Blockchain() {
  Chain.emplace_back(Block(0, "Origin Block"));
  Difficulty = 2;
}

void Blockchain::AddBlock(Block New) {
  *(New.PrevHash) = GetLastBlock().GetHash().c_str();
  New.MineBlock(Difficulty);
  Chain.push_back(New);
}

Block Blockchain::GetLastBlock() const {
  return Chain.back();
}
