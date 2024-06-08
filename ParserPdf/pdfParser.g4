/**
 * FILEPATH: /e:/projects/github/pdf-antlr4/ParserPdf/pdfParser.g4
 
 This grammar file defines the
 * syntax and rules for parsing PDF files using the ANTLR4 parser generator.
 It contains rules for
 * parsing various elements of a PDF file, such as startxref, xref, trailer, pdfObj, etc.
 The
 * grammar is written in ANTLR4 syntax and is intended to be used with the C++ target language.
 
 * Grammar Rules:
 - start: Represents the entry point of the parser. It matches one or more
 * pdfStruct rules.
 - pdfStruct: Represents a PDF structure, which can be startxref, xref, trailer,
 * or pdfObj.
 - startxref: Represents the startxref keyword followed by an integer value.
 -
 * pdfObj: Represents a PDF object. It consists of an integer value, followed by another integer
 * value,
 an optional Obj rule, and zero or more obj rules, followed by the EndObj keyword.
 -
 * trailer: Represents a PDF trailer. It consists of an optional Trailer rule, followed by a dict
 * rule.
 - obj: Represents a PDF object. It can be Null, Int, Boolean, Float, XStr, str, Name,
 * objRef, dict, array, or stream.
 - str: Represents a string enclosed in parentheses. It can
 * contain escape sequences or any other characters.
 - objRef: Represents a PDF object reference.
 * It consists of two integer values, followed by an optional R keyword.
 - xref: Represents the
 * xref keyword followed by one or more subXref rules.
 - subXref: Represents a sub-section of the
 * cross-reference table. It consists of two integer values,
 followed by one or more subXrefEntry
 * rules.
 - subXrefEntry: Represents an entry in the subXref table. It consists of two integer
 * values, followed by either F or N.
 - array: Represents an array enclosed in square brackets. It
 * can contain zero or more obj rules.
 - dict: Represents a dictionary enclosed in double angle
 * brackets. It can contain zero or more key-value pairs,
 where the key is an obj rule and the
 * value is also an obj rule.
 - stream: Represents a stream object. It consists of the Stream
 * keyword followed by the EndStream keyword.
 */
parser grammar pdfParser;
options{
	language = Cpp;
	tokenVocab = pdfLexer;
}
start: pdfStruct+;
pdfStruct: pdfObj | startxref | xref | trailer ;
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
	| xStr
	| str
	| Name
	| objRef
	| dict
	| array
	| stream;
str: Lp Char* Rp;
xStr: Lx HexChar* Rx;
objRef
	locals[bool status=false]:
	Int Int (R {$status=true;})? {$status}?;
array: La obj? obj* Ra;
dict: Ld (obj obj)*? obj? Rd;
stream: Stream EndStream;
xref: Xref subXref+;
subXref: Int Int subXrefEntry+;
subXrefEntry: Int Int (F | N);