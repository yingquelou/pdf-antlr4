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
Stream: 'stream' EOL* Space* -> pushMode(StreamMode);
Lp: '(' -> pushMode(strMode);
Lx: '<' -> pushMode(xstrMode);
fragment D: [0-9];
Int: [+-]? D+;
Float: [+-]? (D+ '.' D+ | D+ '.' | '.' D+);
// Name: '/' (~([ \t\r\n] | '(' | '<' | '[' | '/' | '>' | ']'))+;
Name: '/' (~[ \t\r\n()<>[\]/])+;
Comment: '%' .*? (Lf | EOF) -> skip;
EOL: Space* Lf -> skip;
Lf: Cr? '\n' -> skip;
Space: [ \t] -> skip;
Cr: '\r' -> skip;
Eof: EOF -> skip;

mode StreamMode;
EndStream: EOL* Space* 'endstream' -> popMode;
Byte: . -> channel(streambody);

mode strMode;
Concat: '\\' Space* Lf -> skip;
Char: '\\' (D D? D? | [nrtbf()\\]) | ~[()];
Lp2: '(' -> pushMode(strMode);
Rp: ')' -> popMode;

mode xstrMode;
// HIgnore: ('\u0020' | '\u0009' | '\u000d' | '\u000a' | '\u000c') -> skip;
HIgnore: [ \t\r\n\f] -> skip;
Xchar: [0-9A-Fa-f];
Rx: '>' -> popMode;