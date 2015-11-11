#include "stdafx.h"
#include "E3Run.h" 


E3Run::E3Run(void):_gHitMult(3,std::vector< UInt_32b>(1000,0)),_gSumHitMult(3000,0),
		_gClusterMult(3,std::vector< UInt_32b>(1000,0)),_gSumClusterMult(3000,0)
{
	
	_gLowHitMult=0;
	_gMediumHitMult=0;
	_gHighHitMult=0;
	_gLowClusterMult=0;
	_gMediumClusterMult=0;
	_gHighClusterMult=0;
	_headerParsed=false;
}


E3Run::~E3Run(void)
{
}

UInt_32b E3Run::open(std::string Source,std::string Option)
{

	bool verbose=false;

	if (strcmp("v",Option.c_str())==0) verbose=true;  
	
	
	_sourceStream.open(Source.c_str(),std::ios::binary);

	if(!_sourceStream.good()) 
	{

		std::cout<<"Unable to open input files...reconstruction aborted"<<std::endl;
		return 0;
	}

	//get file size
    _sourceStream.seekg (0, _sourceStream.end);
	_fileLength = _sourceStream.tellg();
    _sourceStream.seekg (0, _sourceStream.beg);
	

	///////////////////////////////////////////////////
	// header parsing (contains gps inforamtion)
	///////////////////////////////////////////////////


	//read Header
	_sourceStream.read((char*)&_headerStruct, sizeof(_headerStruct));  

	if (_headerStruct.Head_begin != 0xfbfbfbfb)
	{
		std::cout<< "Unknown file format..aborting"<<std::endl;
		return 0;
	}

	//print Header Info
	if(verbose) writeHeaderInfo(std::cout);

	
	//read Architecture
	_sourceStream.read((char*)&_archStruct, sizeof(_archStruct));
	if(verbose) writeArchInfo(std::cout); 

	//read GPS
	_sourceStream.read((char*)&_gpsStruct, sizeof(_gpsStruct)); 
	//set and print Gps info
	 setGpsStruct(_gpsStruct);
	if(verbose)writeGpsInfo(std::cout);

	//read WS
	_sourceStream.read((char*)&_wsStruct, sizeof(_wsStruct)); 
	//set and print Gps info
	if(verbose) writeWsInfo(std::cout);
	

	//set event gps timestamp
	setGpsTimestamp(getGpsE3Timestamp());
	//set nino Mapping
	setNinoMap(_archStruct.NINO_map);

	
	_headerParsed=true;
	_analyzed=0;

	return _fileLength;

}

void E3Run::close()
{
	_sourceStream.close();
}

int E3Run::ProcessRawEvent(int FileLength){
  if(_sourceStream.tellg()>=FileLength) return 3;
  E3RecoEvent::clear();
  if(getEvent()==1)
    {
      std::cout<<"Event stream: unexpected fail to read file"<<std::endl;
      return 2;
    }
  
  return unpack();
}

UInt_16b E3Run::analyzeEvent()
{
	if (!_headerParsed)
	{
		std::cout<< "no header parsed yet..."<< std::endl;
		return 2;
	}

	if (_sourceStream.tellg()>=_fileLength)
	{
		std::cout<< "End of File reached"<< std::endl;
		return 1;
	}	
		
	E3RecoEvent::clear();
	
	if(getEvent()==1)
	{
		std::cout<<"Event stream: unexpected fail to read file"<<std::endl;
		return 3;
	}
	if(unpack()!=0)
	{
		std::cout<<"Unpack Failed"<<std::endl;
		return 4;
	}

	_analyzed++;
	//std::cout<<_analyzed<<std::endl;
	
	return 0;


}

void E3Run::analyzeRun(std::string Source,std::string OutDir)
{


	//run calibration

	E3Calib caliber;
	//caliber.importCalibration(caliber.runCalibration(Source,OutDir));
	importCalibration(caliber.runCalibration(Source,OutDir));


	//start analysis
	_sourceStream.open(Source.c_str(),std::ios::binary);
	if(!_sourceStream.good()) 
	{

		std::cout<<"Unable to open input files...reconstruction aborted"<<std::endl;
		return;
	}
	//get file size
    _sourceStream.seekg (0, _sourceStream.end);
	_fileLength = _sourceStream.tellg();
    _sourceStream.seekg (0, _sourceStream.beg);
	

	///////////////////////////////////////////////////
	// header parsing (contains gps inforamtion)
	///////////////////////////////////////////////////

	E3Track bestTrack;

	//read Header
	_sourceStream.read((char*)&_headerStruct, sizeof(_headerStruct));  

	if (_headerStruct.Head_begin != 0xfbfbfbfb)
	{
		std::cout<< "Unknown file format..aborting"<<std::endl;
		return;
	}

	//print Header Info
	writeHeaderInfo(std::cout);

	//read Architecture
	_sourceStream.read((char*)&_archStruct, sizeof(_archStruct));
	writeArchInfo(std::cout); 

	//read GPS
	_sourceStream.read((char*)&_gpsStruct, sizeof(_gpsStruct)); 
	//set and print Gps info
	setGpsStruct(_gpsStruct);
	writeGpsInfo(std::cout);

	//read WS
	_sourceStream.read((char*)&_wsStruct, sizeof(_wsStruct)); 
	//set and print Gps info
	writeWsInfo(std::cout);
	

	//set event gps timestamp
	setGpsTimestamp(getGpsE3Timestamp());


	//generate output files
	if(createOutFile(OutDir)) 
	{

		std::cout<<"Unable to open all output files...reconstruction aborted"<<std::endl;
		return;
	}

	//write file header
	_outFile.WriteHeader();
	_timFile.WriteHeader();
	_2ttFile.WriteHeader();

	//start event loop

	setNinoMap(_archStruct.NINO_map);
	_analyzed=0;
	int GoodEvent=0;
	int trackfound=0;
	while (_sourceStream.tellg()<_fileLength)
	{
		E3RecoEvent::clear();
		if(getEvent()==1)
		{
			std::cout<<"Event stream: unexpected fail to read file"<<std::endl;
			break;
		}
		
		if(unpack()==0)
		{
			if(reconstruct()==0)
			{
				_analyzed++;
				bestTrack=E3RecoEvent::bestTrack();
				getMultiplicity();
				if(numTracks())
				{
					trackfound++;
					if(bestTrack.chisquare() < CHI2THR)	GoodEvent++;

				}
				
				//write event
				_outFile.WriteEntry(_headerStruct.runNumber,(E3Gps)*this,(E3RecoEvent) *this);
				_timFile.WriteEntry(_headerStruct.runNumber,(E3Gps)*this,(E3RecoEvent) *this);
				_2ttFile.WriteEntry(_headerStruct.runNumber,(E3Gps)*this,(E3RecoEvent) *this);
			}
		}
	}
		_sourceStream.close();
		std::cout<<GoodEvent<<std::endl;
		std::cout<<trackfound<<std::endl;
		std::cout<<_analyzed<<std::endl;
		writeRunSum(_sumFile);

		_timFile.close();
		_sumFile.close();
		_outFile.close();
		_2ttFile.close();

}
void E3Run::getMultiplicity()
{
	for (UInt_16b ChamberIdx=0;ChamberIdx<3;ChamberIdx++)
	{
		_gHitMult.at(ChamberIdx).at(numHits(ChamberIdx))++;          //chamber hit multiplicity
		_gClusterMult.at(ChamberIdx).at(numClusters(ChamberIdx))++;	//chamber cluster multiplicity
	}
	if (numHits(0)==0 || numHits(1)==0 || numHits(2)==0) _gLowHitMult++; //at least 1 chamber with no hits
	if (numClusters(0)==1 && numClusters(1)==1 && numClusters(2)==1) _gLowClusterMult++;  //1 cluster in each chamber
	
	if ((numHits(0)==1 || numHits(0)==2)  &&  
		(numHits(1)==1 || numHits(1)==2)  &&
		(numHits(2)==1 || numHits(2)==2)) _gMediumHitMult++;   //events with 1/2 hits in each chamber
	if ((numClusters(0)==2)  &&  
		(numClusters(1)==2)  &&
		(numClusters(2)==2)) _gMediumClusterMult++; //events with 2 clusters in each chamber
	
	if (numHits(0)>2 || numHits(1)>2 || numHits(2)>2) _gHighHitMult++;			//at least one chambers with more than 2 hits
	if (numClusters(0)>2 || numClusters(1)>2 || numClusters(2)>2) _gHighClusterMult++;//at least one chambers with more than 2 cluster

	_gSumHitMult.at(numHits())++;
	_gSumClusterMult.at(numClusters())++;
}

UInt_16b E3Run::getEvent()
{

	UInt_16b nword[2];
	UInt_64b time;
	UInt_32b word;
	
	_sourceStream.read((char*)&time,sizeof(time));
	_sourceStream.read((char*)nword,sizeof(nword[0])*2);
		
	for (UInt_16b i = 0; i < nword[0] + nword[1]; i++) 
	{
		_sourceStream.read((char*)&word, sizeof(word));
		addRawData(word);
	}

	if (_sourceStream.fail()) return 1;

	return 0;
}




std::ostream& E3Run::writeHeaderInfo(std::ostream& os)
{
	os<<"****************** HEADER INFO *****************"<<std::endl<<std::endl;

	os 	<< "Run Name	= " <<	_headerStruct.name<<std::endl
		<< "Run Number	= " <<	_headerStruct.runNumber<<std::endl
		<< "DAQ Version	= " <<	_headerStruct.version<<std::endl
		<< "DAQ Start	= " <<	_headerStruct.StartTime <<std::endl<<std::endl;
	return os;
}

StatusCode E3Run::createOutFile(std::string OutDir)
{
	StatusCode OutputOpening=SUCCESS;	
	std::string fileName;

	fileName=OutDir;
	fileName.append(_headerStruct.name);
	fileName.append(".tim");
	OutputOpening=_timFile.open(fileName);

	fileName.clear();
	fileName=OutDir;
	fileName.append(_headerStruct.name);
	fileName.append(".out");		
	OutputOpening=_outFile.open(fileName);

	fileName.clear();
	fileName=OutDir;
	fileName.append(_headerStruct.name);
	fileName.append(".2tt");	
	OutputOpening=_2ttFile.open(fileName);

	fileName.clear();
	fileName=OutDir;
	fileName.append(_headerStruct.name);
	fileName.append(".sum");
	_sumFile.open(fileName.c_str());
	fileName.append(".sum");
	OutputOpening=_sumFile2.open(fileName);

	if (!(_timFile.good() && _2ttFile.good() && _sumFile.good())) OutputOpening=FAILURE;

	return OutputOpening;
}


std::ostream&	E3Run::writeArchInfo(std::ostream& os)
{

	os<<"****************** ARCHITECTURE INFO *****************"<<std::endl<<std::endl;

	os	
		<< "Trg Mask		= 0x" <<std::hex<<	(UInt_16b)_archStruct.trg_type<<std::endl
		<< "Trg Latency		= " <<std::dec<<_archStruct.trg_latency<<std::endl
		<< "Match window		=	0x" <<_archStruct.match_window<<std::endl
		<< "Search Window		=	0x" <<_archStruct.search_window<<std::endl	
		<< "Window Offset		=	0x" <<std::hex<<_archStruct.window_offset<<std::endl	
		<< "Reject Offset		=	0x" <<std::hex<<_archStruct.reject_offset<<std::endl	
		<< "Detection Mode		=	" <<std::dec<<_archStruct.detection_mode<<std::endl //0 leading, 1 leading&trailing, 2 pairing
		<< "Resolution		= " <<_archStruct.resolution<<std::endl     // ps
		<<"Plane Z Top		=	" << _archStruct.planeDist[0]<<std::endl
		<<"Plane Z Mid		=	" << _archStruct.planeDist[1]<<std::endl
		<<"Plane Z Bot		=	" << _archStruct.planeDist[2]<<std::endl
		<<"Cable TR Length		=	" << _archStruct.cableLength[0]<<std::endl
		<<"Cable TL Length		=	" << _archStruct.cableLength[1]<<std::endl
		<<"Cable MR Length		=	" << _archStruct.cableLength[2]<<std::endl
		<<"Cable ML Length		=	" << _archStruct.cableLength[3]<<std::endl
		<<"Cable BR Length		=	" << _archStruct.cableLength[4]<<std::endl
		<<"Cable BL Length		=	" << _archStruct.cableLength[5]<<std::endl
		<<"Fec TR Type		=	" << (UInt_32b) _archStruct.fecType[0]<<std::endl
		<<"Fec TL Type		=	" << (UInt_32b) _archStruct.fecType[1]<<std::endl
		<<"Fec MR Type		=	" << (UInt_32b) _archStruct.fecType[2]<<std::endl
		<<"Fec ML Type		=	" << (UInt_32b) _archStruct.fecType[3]<<std::endl
		<<"Fec BR Type		=	" << (UInt_32b) _archStruct.fecType[4]<<std::endl
		<<"Fec BL Type		=	" << (UInt_32b) _archStruct.fecType[5]<<std::endl
		<<"Machine ID		=	" <<(UInt_32b) _archStruct.machineID<<std::endl
		<<"Mapping			=	" << _archStruct.NINO_map<<std::endl
		<<"Board Active		=	" << (UInt_32b)_archStruct.Board_plug<<std::endl
		<<"Plane Thickness		=	" << _archStruct.planeThick<<std::endl
		<<"Angle			=	" << _archStruct.orientation<<std::endl
		<<"Signal Speed		=	" << _archStruct.sigSpeed<<std::endl
		<<"Strip Length		=	" << _archStruct.stripLength<<std::endl<<std::endl;

	return os;

}

std::ostream& E3Run::writeWsInfo(std::ostream& os)
{
	os<<"****************** WS INFO *****************"<<std::endl<<std::endl;

	os 	<< "Block Length		=	" <<	_wsStruct.byte<<std::endl
		<< "Block ID		=	" <<   _wsStruct.id<<std::endl
		<< "Date			=	" <<   _wsStruct.year<<"-"<<_wsStruct.month<<"-"<<_wsStruct.day<<std::endl
		<< "Time			=	" <<   _wsStruct.hours<<":"<<_wsStruct.minute<<std::endl
		<< "Outdoor Temp		=	" <<	_wsStruct.outTemp<<std::endl
		<< "Indoor Temp		=	" <<	_wsStruct.inTemp<<std::endl
		<< "Pressure		=	" <<	_wsStruct.pressure<<std::endl<<std::endl;
	return os;
}

std::ostream& E3Run::writeRunSum(std::ostream& os)
{
	os<<" Analyzed events =";
	os.width(13);
	os << std::dec<<std::right<<_analyzed<<std::endl;
	
	os<<"  GPS events";
	os.width(12);
	int aux=0;
	os << std::dec<<std::right<<aux<<std::endl;

	//insert WS format data. dummy for the time being
	os<< std::endl;
	os<<"*****WS line 0********"<<std::endl;
	os<<"*****WS line 1********"<<std::endl;
	os<<"*****WS line 2********"<<std::endl;
	os<<"*****WS line 3********"<<std::endl;
	os<<"*****WS line 4********"<<std::endl;
	os<<"*****WS line 5********"<<std::endl;
	os<<"*****WS line 6********"<<std::endl;
	os<<"*****WS line 7********"<<std::endl;
	os<< std::endl;
	
	//multi hit section
	
	os<<" ****** Hit analysis ***************"<<std::endl;
	 os<<"Events with no hits in a chamber =";
	os.width(13);
	os << std::dec<<std::right<<_gLowHitMult<<std::endl;
	
	 os<<" Events with 1 or 2 hits/chamber =";
	os.width(13);
	os << std::dec<<std::right<<_gMediumHitMult<<std::endl;
	
	 os<<" Event with more than 2 hits in a chamber =";
	os.width(13);
	os << std::dec<<std::right<<_gHighHitMult<<std::endl;
	
	os<<" Hits multiplicity chamber BOTTOM"<<std::endl;
	
	for (int muxIdx = 0; muxIdx < _gHitMult.at(2).size(); muxIdx++)
		if (_gHitMult.at(2).at(muxIdx) > 0)
		{
			os.width(12);
			os <<std::right<<muxIdx;
			os.width(12);
			os <<std::right<<_gHitMult.at(2).at(muxIdx)<<std::endl;
		}
	
	os<<" Hits multiplicity chamber MIDDLE"<<std::endl;
	
	for (int muxIdx = 0; muxIdx < _gHitMult.at(1).size(); muxIdx++)
		if (_gHitMult.at(1).at(muxIdx) > 0)
		{
			os.width(12);
			os <<std::right<<muxIdx;
			os.width(12);
			os <<std::right<<_gHitMult.at(1).at(muxIdx)<<std::endl;
		}
	
	os<<" Hits multiplicity chamber UP"<<std::endl;
	
	for (int muxIdx = 0; muxIdx < _gHitMult.at(0).size(); muxIdx++)
		if (_gHitMult.at(0).at(muxIdx) > 0)
		{
			os.width(12);
			os <<std::right<<muxIdx;
			os.width(12);
			os <<std::right<<_gHitMult.at(0).at(muxIdx)<<std::endl;
		}
	
	os<<" Hits total multiplicity"<<std::endl;
	
	for (int muxIdx = 0; muxIdx < _gSumHitMult.size(); muxIdx++)
		if (_gSumHitMult.at(muxIdx) > 0)
		{
			os.width(12);
			os <<std::right<<muxIdx;
			os.width(12);
			os <<std::right<<_gSumHitMult.at(muxIdx)<<std::endl;
		}
//cluster info (to be adjusted)
		
	os<<" ******** Cluster analysis ************"<<std::endl;
	os<<" Events with 1 cluster in each chamber =";
	os.width(13);
	os << std::dec<<std::right<<_gLowClusterMult<<std::endl;
	
	 os<<" Events with >=2 clusters in a chamber =";
	os.width(13);
	os << std::dec<<std::right<<_gHighClusterMult<<std::endl;
	
	 os<<" Events with 2 clusters  in each chamber =";
	os.width(13);
	os << std::dec<<std::right<<_gMediumClusterMult<<std::endl;

	os<<" Cluster multiplicity chamber BOTTOM"<<std::endl;

	for (int muxIdx = 0; muxIdx < _gClusterMult.at(2).size(); muxIdx++)
		if (_gClusterMult.at(2).at(muxIdx) > 0)
		{
			os.width(12);
			os <<std::right<<muxIdx;
			os.width(12);
			os <<std::right<<_gClusterMult.at(2).at(muxIdx)<<std::endl;
		}

	os<<" Cluster multiplicity chamber MIDDLE"<<std::endl;

	for (int muxIdx = 0; muxIdx < _gClusterMult.at(1).size(); muxIdx++)
		if (_gClusterMult.at(1).at(muxIdx) > 0)
		{
			os.width(12);
			os <<std::right<<muxIdx;
			os.width(12);
			os <<std::right<<_gClusterMult.at(1).at(muxIdx)<<std::endl;
		}

	os<<" Cluster multiplicity chamber UP"<<std::endl;

	for (int muxIdx = 0; muxIdx < _gClusterMult.at(0).size(); muxIdx++)
		if (_gClusterMult.at(0).at(muxIdx) > 0)
		{
			os.width(12);
			os <<std::right<<muxIdx;
			os.width(12);
			os <<std::right<<_gClusterMult.at(0).at(muxIdx)<<std::endl;
		}

	os<<" Cluster total multiplicity"<<std::endl;

	for (int muxIdx = 0; muxIdx < _gSumClusterMult.size(); muxIdx++)
		if (_gSumClusterMult.at(muxIdx) > 0)
		{
			os.width(12);
			os <<std::right<<muxIdx;
			os.width(12);
			os <<std::right<<_gSumClusterMult.at(muxIdx)<<std::endl;
		}

		//other
		 os<< "time cuts"<<std::endl;
			 
	return os;		
}
