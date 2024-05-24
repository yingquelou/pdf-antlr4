lexer grammar BLexer;
options{
	language = Cpp;
	caseInsensitive = true;
}
@lexer::header { 
    #include<fstream>
    #include<string>
 }
@lexer::members { 
}
@lexer::definitions { 
 static std::ofstream ofs("log.txt");
 }
Stream: 'stream' {ofs<<getText();} -> mode(streamMode);
Char: (. | [\r\n]) {ofs<<getText();};
mode streamMode;
EndStream: 'endstream' { ofs.close(); } -> mode(DEFAULT_MODE);
Any: (. | [\r\n]) -> skip;