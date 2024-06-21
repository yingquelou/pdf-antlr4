parser grammar BParser;
options{
	language = Cpp;
	tokenVocab = BLexer;
}

start: Any*;