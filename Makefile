node:
	g++ -std=c++14 walletclient.cpp -Wall -Werror -o wc -lcrypto -lsecp256k1
clean:
	rm -f block*.dat wc
 