# blockchain
Copyright &copy; 2021 devin177

Hello! This is my way of trying to learn how blockchains and cryptocurrencies work.
## 8/2/2021
Wallet function now writes to a wallet.dat file.

- Compile with `make`
- Run with `./node`
- `addblock` to add a block (this is from last time)
- `generatewallet` to generate a wallet file
  - The convention for this is in WALLET.md

## Update 7/29/2021
Big changes today! Finally understand how all the Priv/Pub keys are generated, as well as how they are hashed into wallet addresses.

As of 7/29/2021, you can finally create a wallet address!
- Compile with `make`
- Run with `./node`
- `addblock` to add a block (this is from last time)
- `generateaddress` to generate a wallet address along with the step by step

## Update 7/27/2021
- Need to install secp256k1 from the folder to work?
- Also need libsecp256k1-0 installed (I did `sudo apt-get install libsecp256k1-0
`)

## Update 7/14/2021

As of 7/14/2021, I have placed the private key generation code in a separate header. Not a lot of work done these past 2 weeks. 

## Update 7/1/2021
As of 7/1/2021, I have turned off the `addblock` functionality for the moment. I spent today learning how the creation of Private keys and a lot of the hashing worked for addresses. I am learning this so I can add transactions to the table.

Here's what you CAN do.

- Compile with `make`
- Run with `./node`
  - This will generate a Genesis block and hash, as well as 1 private key for a potential wallet.
- Delete with `make clean`

## Update 6/28/2021
As of 6/28/2021, you can now add blocks to your in RAM blockchain. Clone it and turn these commands to try it out.

- Compile with `make`
- Run with `./node`
  - I changed the naming
- Add a block to the chain using `addblock` when the program is running.
- CTRL-C when finished
- Delete with `make clean`

Notes to Self for the Future
- Transactions are also stored on disk like the blockchain. Will have to look into writing both these things to disk.
- Read something online about serializing the transactions?  into a stream when you send it online? I'm going to have to look into this

## Update 6/22/2021
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

## Ideas for expanding on this

1. Build a fleshed-out POW Coin

2. Build a POS Coin

3. Use blockchain to vote? Secure because votes are immutable

## Works Cited

[tko22](https://github.com/tko22/simple-blockchain)\
[Dave Nash](https://davenash.com/2017/10/build-a-blockchain-with-c/)\
[Nick Farrow](https://nickfarrow.com/Cryptography-in-Bitcoin-with-C/)\
[bitcoinbook](https://cypherpunks-core.github.io/bitcoinbook/)\
[ProgrammerSought/Bitcoin0.16](https://www.programmersought.com/article/19961775751/)\
[StackOverflow Hex Function](https://stackoverflow.com/questions/3381614/c-convert-string-to-hexadecimal-and-vice-versa)
