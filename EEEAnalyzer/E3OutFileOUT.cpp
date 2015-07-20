#include "stdafx.h"


E3OutFileOUT::E3OutFileOUT(void)
{
}


E3OutFileOUT::~E3OutFileOUT(void)
{
}



void E3OutFileOUT::WriteHeader()
{

	*this << " run_number,event_number,secs_since_1.1.2007,nanosec,microseconds_since_start_of_run track:"
		<<",posX_Bottom,posY_Bottom,time_Bottom,posX_Middle,posY_Middle,time_Middle,posX_Top,posY_Top,"
		<<"time_Top,intersect_middle_X,intersect_middle_Y,intersect_middle_Z,unit_vector_x,unit_vector_y,"
		<<"unit_vector_z,hitted_Strips_Bottom,hitted_Strips_Middle,hitted_Strips_Top,clusters_Bottom,"
		"clusters_Middle,clusters_Top,chi_squared,time of flight[ns],track length[cm]" << std::endl<<std::dec<<std::fixed;


}

void E3OutFileOUT::WriteEntry(UInt_32b runNumber, E3Gps Gps, E3RecoEvent evt)
{


	write(runNumber);							//run number from header
	write(evt.getEvtNum()-1,15);				//event number(corrected for 1 event offset)

	E3Track bestTrack;
	if (!evt.numTracks())   // if no tracks are reconstructed,write it and return
	{ 
		write(" no hit");
		endline();
		return;
	}
	else bestTrack=evt.bestTrack();


	write(evt.getEvtSec()+Gps.getGpsE3Timestamp(),15);//seconds from 1.1.2007

	long clkNum=evt.getEvtBunch()+evt.getEvtOrbit()*4000;
	long nsec=1.0/(double)(evt.getEvtCal())*(double)clkNum/1e-9;
	write(nsec,15);			//nanosecond from last PPS


	long micro=nsec/1000+evt.getEvtSec()*1000000;
	write(micro,15);//micro from run start

	//track cluster coordinates
	write(bestTrack.cluster(kBotPlane).x(),15);  
	write(bestTrack.cluster(kBotPlane).y(),15);  
	write(bestTrack.cluster(kBotPlane).hitTime(),15);  
	write(bestTrack.cluster(kMidPlane).x(),15);  
	write(bestTrack.cluster(kMidPlane).y(),15);  
	write(bestTrack.cluster(kMidPlane).hitTime(),15);
	write(bestTrack.cluster(kTopPlane).x(),15);  
	write(bestTrack.cluster(kTopPlane).y(),15);  
	write(bestTrack.cluster(kTopPlane).hitTime(),15);  

	//intersect
	write(0.0,15);  // intersect middle x
	write(0.0,15);  // intersect middle y
	write(80,15);  // intersect middle z

	//cosine direction
	write(bestTrack.xdir(),10,5);
	write(bestTrack.ydir(),10,5);
	write(bestTrack.zdir(),10,5);

	//hit numbers
	write(evt.numHits(kBotPlane),15);
	write(evt.numHits(kMidPlane),15);
	write(evt.numHits(kTopPlane),15);

	//cluster numbers
	write(evt.numClusters(kBotPlane),15);
	write(evt.numClusters(kMidPlane),15);
	write(evt.numClusters(kTopPlane),15);

	//chi2
	write(bestTrack.chisquare(),9,3);

	//tof
	write(bestTrack.timeOfFlight(),11,3);

	//track L
	write(bestTrack.length(),11,2);

	endline();
		
}