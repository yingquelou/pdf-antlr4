lexer grammar BLexer;
options{
	language = Cpp;
	caseInsensitive = true;
}

Stream: 'stream' -> mode(streamMode);
Char: (. | [\r\n]);
mode streamMode;
EndStream: 'endstream' -> mode(DEFAULT_MODE);
Any: (. | [\r\n]) -> skip;