lexer grammar BLexer;
options{
	language = Cpp;
}
@ lexer:: members {

}
PDEOF: '%%EOF' ;
Ignore: EOF -> skip;
Any: .;
