#include "stdafx.h"
#include "E3OutFileTIM.h" 



E3OutFileTIM::E3OutFileTIM(void)
{
}


E3OutFileTIM::~E3OutFileTIM(void)
{
}



void E3OutFileTIM::WriteHeader()
{

	
	*this << "  run_number,event_number,event_timesecs since 1.1.2007,nanosec"<<std::endl<<std::dec<<std::fixed;

}

void E3OutFileTIM::WriteEntry(UInt_32b runNumber, E3Gps Gps, E3RecoEvent evt)
{

	write(runNumber,6);							//run number from header
	write(evt.getEvtNum()-1,11);				//event number(corrected for 1 event offset)


	write(evt.getEvtSec()+Gps.getGpsE3Timestamp(),11);//seconds from 1.1.2007

	long clkNum=evt.getEvtBunch()+evt.getEvtOrbit()*4000;
	long nsec=1.0/(double)(evt.getEvtCal())*(double)clkNum/1e-9;
	write(nsec,11);			//nanosecond from last PPS

	endline();
		
}
