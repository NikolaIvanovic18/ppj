parser : parser.o lexer.o sintaksno.o
	g++ -std=c++11 parser.o lexer.o sintaksno.o -o parser

sintaksno.o : sintaksno.cpp
	g++ -std=c++11 -c sintaksno.cpp -o sintaksno.o

lexer.o : lex.yy.c parser.tab.hpp
	g++ -std=c++11 -c lex.yy.c -o lexer.o

parser.o : parser.tab.cpp parser.tab.hpp
	g++ -std=c++11 -c parser.tab.cpp -o parser.o

lex.yy.c : lexer.l
	flex lexer.l

parser.tab.cpp parser.tab.hpp : parser.ypp
	bison -d -v parser.ypp

.PHONY: clean

clean : 
	rm -rf *.yy.* *.tab.* *.output *.o parser