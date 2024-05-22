lexer grammar mathLexer;
options{
	language = Cpp;
}
Space: [ \t\r\n]+ -> skip;
Ld: '<<';
Rd: '>>';
La: '[';
Ra: ']';
fragment D: [0-9];
Obj: 'obj';
R: 'R' ;
EndObj: 'endobj';


// pdf原子对象
Boolean:'false'|'true';
Int: [+-]? D+;
Float: [+-]? (D+ '.' D+ | D+ '.' | '.' D+);
XStr: '<' [0-9A-Fa-f]*? '>';
Str: '(' ~')'*? ')';
Name: '/' (~([ \t\r\n] | '(' | '<' | '[' | '/'))+;
FE: EOF -> skip;
// EOL: [\r\n]+;
// Comment: '%' .*? EOL -> skip;
// mode objMode;
// Obj: D+ D+ 'obj' -> mode(DEFAULT_MODE);

// mode rMode;
// R: D+ D+ 'R' -> mode(DEFAULT_MODE);
mode StreamMode;
EndStream: 'endstream' -> mode(DEFAULT_MODE);
Sp: [ \r\n\t] -> skip;
Any: .;
mode DEFAULT_MODE;
Stream: 'stream' -> mode(StreamMode);