lexer grammar BLexer;
options{
	language = Cpp;
}
@ lexer:: members {
public:
	void emitErrorMessage(const std::string& msg) {
		std::cerr << msg << std::endl;
	}
}
PDEOF: '%%EOF' ;
Ignore: EOF -> skip;
Any: .;
