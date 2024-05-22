parser grammar mathParser;
options{
	language = Java;
	language = Cpp;
	tokenVocab = mathLexer;
}
@parser::header { 
 }
start: ( pdfObj | startxref)+;
startxref: Startxref Int;
pdfObj
	locals[bool status=false]:
	Int Int (Obj {$status=true;})? {$status}? obj* EndObj;
// pdf复合对象
obj:
	Int
	| Boolean
	| Float
	| XStr
	| Str
	| Name
	| objRef
	| dict
	| array
	| stream;
objRef
	locals[bool status=false]:
	Int Int (R {$status=true;})? {$status}?;

array: La obj? obj* Ra;
dict: Ld (obj obj)*? obj? Rd;
// int: | Int {std::cout<<$Int->Show();};
stream: Stream Any*? EndStream;