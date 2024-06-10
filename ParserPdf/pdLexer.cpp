#include "pdLexer.h"
antlr4::Token *pdLexer::emit()
{
	static std::stringstream out;
	static std::ofstream ofs;
	if (this->channel == pdfLexer::streambody)
	{
		out << this->getText();
	}
	else if (this->type == pdfLexer::Int)
	{
		indexEntryVector.push(this->getText());
	}
	else if (this->type == pdfLexer::Obj)
	{
		if (indexEntryVector.size() == 2)
		{
			index = indexEntryVector.front();
			gen = indexEntryVector.back();
			count = 1;
		}
	}
	else if (this->type == pdfLexer::Stream)
	{
		setText("stream");
		out.str("");
	}
	else if (this->type == pdfLexer::EndStream)
	{
		setText("endstream");
		if (ofs.is_open())
			ofs.close();
		ofs.open(index + "_" + gen + "_" + std::to_string(count++) + ".stream");
		ofs << out.str();
	}
	return pdfLexer::emit();
}