parser grammar pdfParser;
options{
	language = Cpp;
	tokenVocab = pdfLexer;
}
start: pdfStruct+;
pdfStruct: startxref | xref | trailer | pdfObj;
startxref: Startxref Int;
pdfObj
	locals[bool status=false]:
	Int Int (Obj {$status=true;})? {$status}? obj* EndObj;
trailer
	locals[bool status=false]: (Trailer {$status=true;})? { $status }? dict;
// pdf复合对象
obj:
	Null
	| Int
	| Boolean
	| Float
	| XStr
	| str
	| Name
	| objRef
	| dict
	| array
	| stream;
str: Lp (ESC | AnyStr)* Rp;
objRef
	locals[bool status=false]:
	Int Int (R {$status=true;})? {$status}?;
xref: Xref (Int Int (Int Int (F | N))+)+;
array: La obj? obj* Ra;
dict: Ld (obj obj)*? obj? Rd;
stream: Stream Any*? EndStream;