parser grammar BParser;
options{
	language = Cpp;
	tokenVocab = BLexer;

}

start: (Any{std::cout<<$Any.text;})*;

// start: (Any {std::cout << $Any.text;})* EOF ( (Any {std::cout << $Any.text;})* EOF )*;