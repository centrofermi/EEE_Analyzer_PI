#include "stdafx.h"
#include "E3Event.h"




E3Event::E3Event(void):_rawDataVec(0,0)
{
	
}


void E3Event::clear(void)
{
	_rawDataVec.clear();
	for (UInt_16b plane = 0; plane < 3; plane++) {
    m_stripDataVec[plane].clear();
  }
}
E3Event::~E3Event(void)
{
}


void E3Event::addStripData(UInt_16b plane, E3StripData data)
{
  m_stripDataVec[plane].push_back(data);
}


UInt_16b E3Event::numStripData(UInt_16b plane) 
{
  return m_stripDataVec[plane].size();
}


UInt_16b E3Event::numStripData() 
{
  unsigned short n = 0;
  for (UInt_32b plane = 0; plane < 3; plane++) {
    n += numStripData(plane);
  }
  return n;
}


UInt_16b E3Event::unpack()
{
	// We need to organize the data by plane and channel so that we 
	// can group together the information for creating the E3StripData object
	// to fill the m_stripDataVec class member with.
	E3RawMap rawMap;

	//create raw data iterator
	E3RawDataVecIter iter=_rawDataVec.begin();

	//start the loop

	for (UInt_16b boardIdx=0; boardIdx<=1; boardIdx++)  //loop sulle board  
	{
		if(!iter->isBoardBegin())
		{
			std::cout<<"Warning: No board begin found in event "<< _evtNum <<" board "<<boardIdx<<". Event analysis skipped" << std::endl;
			return 1;
		}
		
		UInt_32b NINO_id=0xf;

		if (boardIdx==0)
		{
			_evtNum =	(++iter)->digiWord();		// get event number
			_trgNum	=	(++iter)->digiWord();		// get trigger number
			_sec	=	(++iter)->digiWord();		// get sec from run start 
			_orbit	=	(((++iter)->digiWord()) >> 16) & 0xffff; //get orbit number
			_bunch	=	(iter->digiWord()) & 0xffff;			 //get bunch number
			_calib	=	(++iter)->digiWord();					 //get calibration value
		}
		else iter+=5;

		for (UInt_16b TDCIdx=0;TDCIdx<=3;TDCIdx++)  //loop sui 4 tdc 
		{
			NINO_id=(_ninoMap>>(16*boardIdx+4*TDCIdx))&0xf;  //extract nino id
			UInt_16b plane	=	NINO_id/2; //(0,1=plane0; 2,3=plane1; 4,5=plane2)
			UInt_16b side	=	NINO_id%2; //(0,2,4=positive; 1,3,5=negative)
			//std::cout<< NINO_id<<"		"<< _fecType[NINO_id]<< std::endl;

			if (!((++iter)->isTdcBegin(TDCIdx))) //cerco l'inizio del TDC
			{
				std::cout<<"Warning: No TDC "<<TDCIdx<<" header found in event "<< _evtNum <<" board "<<boardIdx<<". Event analysis skipped" << std::endl;
				iter->fillStream(std::cout);
				return 2;
			}

			if (!((++iter)->isTdcHeader()))  //detection of TDC header
			{
				std::cout<<"Warning: No TDC "<<TDCIdx<<"internal header found in event "<< _evtNum <<" board "<<boardIdx<<". Event analysis skipped" << std::endl;
				return 3;
			}
				
			while (!((++iter)->isTdcTrailer())) //loop fino alla fine dell'evento del TDC
			{
				if (iter == (_rawDataVec.end()-1)) //cerco l'inizio del TDC
				{
					std::cout<<"Warning: No TDC "<<TDCIdx<<" internal trailer found in event "<< _evtNum <<" board "<<boardIdx<<". Event analysis skipped" << std::endl;
					return 4;
				}
				if (iter->isEdge() && NINO_id!=0xf )
				{
					E3RawMapKey key;
					if (NINO_id%2==0) // positive nino, should be V1
					{
						if (_fecType[NINO_id]==1)
							 key = std::make_pair(plane, iter->getChannel());
						else
							 key = std::make_pair(plane,23 - iter->getChannel());
					}
					else //negative NINO, should be V3
					{
						if (_fecType[NINO_id]==3)
							 key = std::make_pair(plane, iter->getChannel());
						else
							 key = std::make_pair(plane,23 - iter->getChannel());
					}
					rawMap[key].push_back(std::make_pair(side, *iter));
				}
			}
			if(!((++iter)->isTdcEnd()))
			{
				std::cout<<"Warnig: No TDC "<<TDCIdx<<" trailer found in event "<< _evtNum <<" board "<<boardIdx<<". Event analysis skipped" << std::endl;
				return 5;
			}
		}

		if(!((++iter)->isBoardEnd()))
		{
			std::cout<<"Warnig: No Board end found in event "<< _evtNum <<" board "<<boardIdx<<". Event analysis skipped" << std::endl;
			return 6;
		}
		++iter;
	}

	// Finally: we're ready to parse the digiMap object and fill the
	// m_stripDataVec class member.
	for (E3RawMapIter item = rawMap.begin(); item != rawMap.end(); item++) {
	  E3StripData stripData(item->first.first, item->first.second);
	  E3RawMapValue mapValue = item->second;
	  for (E3RawMapValueIter value = mapValue.begin(); value != mapValue.end();
		 value++) {
	    stripData.addEdgeDigi(value->first, value->second);
	  }
		/*stripData.fillStream(std::cout);
		std::cout<<std::endl;*/
	  addStripData(item->first.first, stripData);
	}
	return 0;
}