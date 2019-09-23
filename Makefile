GED: parserout
	./unitTest gedcomTest.ged
	./parser gedcomTest.ged

parserout: parser.cpp
	g++ main.cpp parser.cpp monaco.cpp -std=c++11 -o parser
	g++ main.cpp parser.cpp monaco.cpp -std=c++11 -o unitTest
clean:
	rm -f *.out *.o parser unitTest
