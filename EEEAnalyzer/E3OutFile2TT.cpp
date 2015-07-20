#include "stdafx.h"



E3OutFile2TT::E3OutFile2TT(void)
{
}


E3OutFile2TT::~E3OutFile2TT(void)
{
}



void E3OutFile2TT::WriteHeader()
{

	*this << " run_number,event_number,secs_since_1.1.2007,nanosecs,posX_Bottom,posY_Bottom,posX_Middle,"
		<<"posY_Middle,posX_Top,posY_Top,intersect_middle_X,intersect_middle_Y,intersect_middle_Z,"
		<<"unit_vector_x,unit_vector_y,unit_vector_z,chi_squared,time of flight[ns],track length[cm],"
		<<"track2: unit_vector_x,unit_vector_y,unit_vector_z,hitted_Strips_Bottom,hitted_Strips_Middle,"
		<<"hitted_Strips_Top,clusters_Bottom,clusters_Middle,clusters_Top,chi_squared,time of flight[ns],"
		<<"track length[cm]" << std::endl<<std::dec<<std::fixed;

}

void E3OutFile2TT::WriteEntry(UInt_32b runNumber, E3Gps Gps, E3RecoEvent evt)
{
		
}
