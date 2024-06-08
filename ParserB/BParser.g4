parser grammar BParser;
options{
	language = Cpp;
	tokenVocab = BLexer;
}

start: Any*;

// start: (Any {std::cout << $Any.text;})* EOF ( (Any {std::cout << $Any.text;})* EOF )*;