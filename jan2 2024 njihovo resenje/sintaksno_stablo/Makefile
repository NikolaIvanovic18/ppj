parser: parser.o lexer.o stable.o stree.o
	g++ parser.o lexer.o stable.o stree.o -o parser

stree.o: SyntaxTree.cpp SyntaxTree.hpp
	g++ -c SyntaxTree.cpp -o stree.o

stable.o: SymbolTable.cpp SymbolTable.hpp
	g++ -c SymbolTable.cpp -o stable.o

parser.o: parser.tab.cpp parser.tab.hpp
	g++ -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c
	g++ -c lex.yy.c -o lexer.o

lex.yy.c: lexer.l parser.tab.hpp
	flex -l lexer.l

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp

.PHONY: clean

clean: 
	rm -rf *.output *.tab.* *.yy.* *.o parser