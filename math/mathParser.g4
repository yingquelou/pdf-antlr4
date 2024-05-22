parser grammar mathParser;
options{
	language = Cpp;
	tokenVocab = mathLexer;
}
@parser::header { 
	// #define Show toString
	#define Show getText
 }
start
	locals[bool status=false]: (
		Int Int (Obj {$status=true;})? {$status}? {std::cout<<"obj";} obj* EndObj {std::cout<<"endobj\n";
			}
	)+;
// pdf复合对象
obj:
	Int {std::cout<<$Int->Show();}
	| Boolean {std::cout<<$Boolean->Show();}
	| Float {std::cout<<$Float->Show();}
	| XStr {std::cout<<$XStr->Show();}
	| Str {std::cout<<$Str->Show();}
	| Name {std::cout<<$Name->Show();}
	| objRef
	| dict
	| array
	| stream;
objRef
	locals[bool status=false]:
	Int Int (R {$status=true;})? {$status}? {std::cout<<$R->Show();};

array:
	La {std::cout<<$La->Show();} obj? ({std::cout<<' ';} obj)* Ra {std::cout<<$Ra->Show();};
dict:
	Ld {std::cout<<"<<";} ({std::cout<<'\n';} obj {std::cout<<' ';} obj)*? (
		{std::cout<<'\n';} obj
	)? Rd {std::cout<<"\n>>";};
// int: | Int {std::cout<<$Int->Show();};
stream:
	Stream {std::cout<<$Stream->Show();} Any*? EndStream {std::cout<<$EndStream->Show();};