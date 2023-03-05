prog: main.o
		g++ -g main.o cancerdata.o -o PA3

main.o: main.cpp AVLTree.h AVLNode.h CancerData.h
		g++ -c -g -Wall -std=c++11 main.cpp

cancerdata.o: CancerData.cpp CancerData.h
		g++ -c -g -Wall -std=c++11 CancerData.cpp

clean:
		-rm *.o

run: @./PA3