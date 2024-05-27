lexer grammar pdfLexer;
options{
	language = Cpp;
}
Space: [ \t\r\n]+ -> skip;
XStr: '<' [0-9A-Fa-f]*? '>';
Trailer: 'trailer';
Ld: '<<';
Rd: '>>';
La: '[';
Ra: ']';
fragment D: [0-9];
Null: 'null';
Obj: 'obj';
R: 'R';
EndObj: 'endobj';
Startxref: 'startxref';
Xref: 'xref';
F: 'f';
N: 'n';
Lp: '(' -> mode(strMode);
// pdf原子对象
Boolean: 'false' | 'true';
Int: [+-]? D+;
Float: [+-]? (D+ '.' D+ | D+ '.' | '.' D+);
Name: '/' (~([ \t\r\n] | '(' | '<' | '[' | '/' | '>' | ']'))+;

EOL: (EOF | [\r\n]+) -> skip;
Comment: '%' .*? EOL -> skip;
Stream: 'stream' [ \r\n]* -> mode(StreamMode);

mode strMode;
ESC: '\\' (D D? D? | [nrtbf] | '\\' | '(' | ')');
AnyStr: ~')';
Rp: ')' -> mode(DEFAULT_MODE);

mode StreamMode;
EndStream: [ \r\n\t]* 'endstream' -> mode(DEFAULT_MODE);
Any: .;