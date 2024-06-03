#include "pdLexer.h"

antlr4::Token *pdLexer::emit()
{
    if(this->channel == pdfLexer::streambody){
		out << this->getText();
	}else if(this->type == pdfLexer::Int){
		indexEntryVector.push(this->getText());
	}else if(this->type == pdfLexer::Obj){
		if(indexEntryVector.size() == 2){
			index = indexEntryVector.front();
			gen = indexEntryVector.back();
			count = 1;
		}
	}else if (this->type == pdfLexer::Stream){
		out.open(index + "_" + gen + "_" + std::to_string(count++) + ".stream",std::ios_base::binary);
	}else if (this->type == pdfLexer::EndStream){
		out.close();
		}
		this->addErrorListener(new antlr4::ConsoleErrorListener());
	return	pdfLexer::emit();
}