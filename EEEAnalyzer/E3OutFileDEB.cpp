#include "stdafx.h"
#include "E3OutFileDEB.h"



E3OutFileDEB::E3OutFileDEB(void)
{
}


E3OutFileDEB::~E3OutFileDEB(void)
{
}



void E3OutFileDEB::WriteHeader()
{

	*this << "EvtNum	Track	GoodTracks" << std::endl<<std::dec<<std::fixed;

}

void E3OutFileDEB::WriteEntry(E3RecoEvent evt)
{

	write(evt.getEvtNum()-1,15);				//event number(corrected for 1 event offset)
	write(evt.numTracks(),9);
	write(evt.numGoodTracks(),9);
	endline();
		
}
