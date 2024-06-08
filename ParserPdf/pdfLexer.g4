/**
 * This is the lexer grammar for parsing PDF files.
 It defines the token rules and lexer modes for
 * the PDF lexer.
 The lexer rules include patterns for whitespace, strings, numbers, names, and
 * other PDF syntax elements.
 The lexer modes handle special cases such as string literals and
 * stream bodies.
 */
lexer grammar pdfLexer;
options{
	language = Cpp;
}
channels {
	streambody
}
EOL: '\r'? '\n' -> skip;
Space: ' ' -> skip;
Trailer: 'trailer';
Ld: '<<';
Rd: '>>';
La: '[';
Ra: ']';
Null: 'null';
Obj: 'obj';
R: 'R';
EndObj: 'endobj';
Startxref: 'startxref';
Xref: 'xref';
F: 'f';
N: 'n';
Lp: '(' -> mode(strMode);
Boolean: 'false' | 'true';
Lx: '<' -> mode(hstrMode);
fragment D: [0-9];
Int: [+-]? D+;
Float: [+-]? (D+ '.' D+ | D+ '.' | '.' D+);
Name: '/' (~([ \t\r\n] | '(' | '<' | '[' | '/' | '>' | ']'))+;

Comment: '%' .*? (EOF | Space+) -> skip;
Stream: 'stream' Space* -> mode(StreamMode);

mode StreamMode;
EndStream: Space* 'endstream' -> mode(DEFAULT_MODE);
Byte: . -> channel(streambody);

mode strMode;
Concat: '\\' [ \t]* EOL -> skip;
Char: '\\' (D D? D? | [nrtbf] | '\\' | '(' | ')') | ~')';
Rp: ')' -> mode(DEFAULT_MODE);
mode hstrMode;
HIgnore: Space -> skip;
HexChar: [0-9A-Fa-f];
Rx: '>' -> mode(DEFAULT_MODE);
