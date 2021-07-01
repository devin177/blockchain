# blockchain
Copyright &copy; 2021 devin177

Hello! This is my way of trying to learn how blockchains and cryptocurrencies work.

### Update 7/1/2021
Making this actually secure is going to be almost impossible LOL.

### Update 6/28/2021
As of 6/28/2021, you can now add blocks to your in RAM blockchain. Clone it and turn these commands to try it out.

- Compile with `make`
- Run with `./node`
  - I changed the naming
- Add a block to the chain using `addblock` when the program is running.
- CTRL-C when finished
- Delete with make clean

Notes to Self for the Future
- Transactions are also stored on disk like the blockchain. Will have to look into writing both these things to disk.
- Read something online about serializing the transactions?  into a stream when you send it online? I'm going to have to look into this

### Update 6/22/2021
As of 6/22/2021, what this program allows you to do is simulate creating the genesis block for an unnamed cryptocurrency. Clone it if you want to test it out.

- Compile with "make"
- Run with "./bc"
- Delete with "make clean"

- I have learned a lot about this topic over the last few days, but I am getting confused by trying to understand too many things about the blockchain at once. So, I'm going to set a plan in motion.

1. Set up the basic blockchain data structure (Using an in-memory vector as my blockchain)

2. Set up a basic web server to allow others to connect to this (singular at the moment node)
 - Addendum: Implement a function that changes things to JSON

3. Change the way the blockchain is actually stored/learn how to write and format the ".dat" files that bitcoin seems to use

4. Multiple Nodes/conflicting blockchains/etc. problems

### Ideas for expanding on this

1. Build a fleshed-out POW Coin

2. Build a POS Coin

3. Use blockchain to vote? Secure because votes are immutable

## Works Cited

[tko22](https://github.com/tko22/simple-blockchain)
[Dave Nash](https://davenash.com/2017/10/build-a-blockchain-with-c/)
