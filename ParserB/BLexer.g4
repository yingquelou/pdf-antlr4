lexer grammar BLexer;
options{
	language = Cpp;
}

PDEOF: '%%EOF' ;
Ignore: EOF -> skip;
Any: .;