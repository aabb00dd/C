compiler: lex.yy.c main.cc
		g++ -g -w -o compiler lex.yy.c main.cc -std=c++14
lex.yy.c:
		flex minijava_language.flex
clean:
		rm -f lex.yy.c* compiler