node:
	g++ -std=c++14 node.cpp -Wall -Werror -o node -lcrypto -lsecp256k1
clean:
	rm -f node
