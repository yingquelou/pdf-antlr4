parser grammar pdfParser;
options{
	language = Cpp;
	tokenVocab = pdfLexer;
}
pdf: (startxref | xref | trailer | pdfObj)+;
startxref: Startxref Int;
pdfObj
	locals[bool status=false]:
	Int Int (Obj {$status=true;})? {$status}? obj* EndObj;
trailer
	locals[bool status=false]: (Trailer {$status=true;})? { $status }? dict;
obj:
	Null
	| Int
	| Boolean
	| Float
	| Name
	| xStr
	| str
	| objRef
	| dict
	| array
	| stream;
str: Lp Char* Rp;
xStr: Lx Xchar* Rx;
objRef
	locals[bool status=false]:
	Int Int (R {$status=true;})? {$status}?;
array: La obj? obj* Ra;
dict: Ld (obj obj)*? obj? Rd;
stream: Stream EndStream;
xref: Xref subXref+;
subXref: Int Int subXrefEntry+;
subXrefEntry: Int Int (F | N);