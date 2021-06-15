#include "block.h"

Block::Block(uint32_t IndexIn, const string &DataIn) : Index(IndexIn), Data(DataIn) {
  Nonce = -1;
  Time = time (nullptr);
}
