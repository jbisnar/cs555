GED: parserout
	./unitTest
	rm unitTest.exe
parserout: parser.cpp
	g++ main.cpp parser.cpp monaco.cpp -std=c++11 -o parser
	g++ unitTest.cpp parser.cpp monaco.cpp -std=c++11 -o unitTest
clean:
	rm -f *.out *.o parser unitTest
