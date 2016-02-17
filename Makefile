compute: lex.yy.c rdp_parser.c arraylist.c arraylist.h tokens.h
	gcc -o compute arraylist.c rdp_parser.c lex.yy.c -ll

lex.yy.c:	expr.l
	flex expr.l
