GED: parserout
	./unitTest
	rm unitTest
parserout: parser.cpp
	g++ main.cpp parser.cpp bisnar.cpp monaco.cpp dytioco.cpp -std=c++11 -o parser
	g++ unitTest.cpp parser.cpp bisnar.cpp monaco.cpp dytioco.cpp -std=c++11 -o unitTest
clean:
	rm -f *.out *.o parser unitTest
