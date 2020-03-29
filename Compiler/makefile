program: parser.y lexer.l
		bison -d parser.y --debug
		lex -o lexer.yy.c lexer.l 
		g++ -o compiler lexer.yy.c parser.tab.c -ll -lm 
clean:
		rm parser.tab.c parser.tab.h lexer.yy.c $(OBJ) compiler
