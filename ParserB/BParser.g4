parser grammar BParser;
options{
	language = Cpp;
	tokenVocab = BLexer;
}
@parser::header { 
    #include<fstream>
    #include<string>
    #include<exception>
 }
@parser::members { 
}
@parser::definitions { 
 static std::ofstream ofs("log.txt");
 }
start: (Char {ofs<<$Char.text;})*? (
		Stream EndStream (Char {ofs<<$Char.text;})*?
	)*;
