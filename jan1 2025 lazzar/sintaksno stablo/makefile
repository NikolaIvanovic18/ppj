CXX = g++
CXXFLAG = -Wall -Wextra --pedantic -g -c

izvrsni: parser.tab.o lex.yy.o
	$(CXX) $^ -o $@

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) $(CXXFLAG) $<

lex.yy.o: lex.yy.c
	$(CXX) $(CXXFLAG) $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<

lex.yy.c: lex.l
	flex $<

.PHONY: clean

clean:
	rm -rf *.o izvrsni parser.tab.* lex.yy.* parser.output