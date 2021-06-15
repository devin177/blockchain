bc:
	g++ -std=c++11 main.cpp block.cpp blockchain.cpp sha256.cpp -o bc
clean:
	rm -f bc
