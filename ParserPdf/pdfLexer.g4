lexer grammar pdfLexer;
options{
	language = Cpp;
}
channels {
	streambody
}
Trailer: 'trailer';
Null: 'null';
EndObj: 'endobj';
Obj: 'obj';
Boolean: 'false' | 'true';
Startxref: 'startxref';
Xref: 'xref';
R: 'R';
F: 'f';
N: 'n';
Ld: '<<';
Rd: '>>';
La: '[';
Ra: ']';
Stream: 'stream' Space* -> mode(StreamMode);
Lp: '(' -> mode(strMode);
Lx: '<' -> mode(xstrMode);
fragment D: [0-9];
Int: [+-]? D+;
Float: [+-]? (D+ '.' D+ | D+ '.' | '.' D+);
Name: '/' (~([ \t\r\n] | '(' | '<' | '[' | '/' | '>' | ']'))+;
EOL: '\r'? '\n' -> skip;
Space: [ \r\n\t] -> skip;
Comment: '%' .*? (EOL | EOF) -> skip;

mode StreamMode;
EndStream: Space* 'endstream' -> mode(DEFAULT_MODE);
Byte: . -> channel(streambody);

mode strMode;
Concat: '\\' [ \t]* EOL -> skip;
Char: '\\' (D D? D? | [nrtbf] | '\\' | '(' | ')') | ~')';
Rp: ')' -> mode(DEFAULT_MODE);

mode xstrMode;
HIgnore: Space+ -> skip;
Xchar: [0-9A-Fa-f];
Rx: '>' -> mode(DEFAULT_MODE);