GED: parserout
	./parser gedcomTest.ged

parserout: parser.cpp
	g++ parser.cpp -std=c++11 -o parser

clean:
	rm -f *.out *.o parser
