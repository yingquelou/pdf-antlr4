%{
#define PDFLEX
#include <pdf.config.h>
%}
La \[
Ra \]
Ld "<<"
Rd ">>"
Str \(.*\)
Xstr \<{Xd}*\>
D [0-9]
Xd [0-9A-Fa-f]
F [+-]?{D}*\.{D}+
Obj {Int}{Space}+{Int}{Space}+obj
Int [+-]?{D}+
R {Int}({Space}|{CrLf})+{Int}({Space}|{CrLf})+R
Space " "
CrLf \r?\n
Name \/[^ \/\\\t\r\n\[\]\<\(\)\>]+
%%
trailer {
	return TRAILER;
}
null {
	return PDNULL;
}
endobj {
	return ENDOBJ;
}
{Obj} {
	return OBJ;
}
true {
	return BOOLEAN;
}
false {

	return BOOLEAN;
}
startxref {
return STARTXREF;
}
xref {
	return XREF;
}
{CrLf} {}
{Space} {}
{Int}   {
	return INTEGER;
}
{F}     {

	return REAL;
}
^{Int}{Space}+{Int}{Space}*{CrLf} {
	return SUBXREFHEAD;
}
^{D}{10}{Space}+{D}{5}{Space}+f{Space}*{CrLf} {

	return FXREFENTRY;
}
^{D}{10}{Space}+{D}{5}{Space}+n{Space}*{CrLf} {

	return NXREFENTRY;
}
{Name} {

	return NAME;
}
{Str} {

	return STRING;
}
{Xstr} {
	return XSTRING;
}

{R} {

	return INDIRECTOBJREF;
}

{Ld} {
	return LD;
}
{Rd} {
	return RD;
}
{La} {
	return '[';
}
{Ra} {
	return ']';
}

{CrLf}*endstream {

return ENDSTREAM;
}
stream{CrLf}* {

return STREAM;
}

%.*{CrLf} {
}
%%
int yywrap()
{
		return(1);
}
