#include "stdafx.h"


E3Calib::E3Calib(void):_YTrend(3,TGraph(24)),_TTrend(3,TGraph(24)),_rawYMatrix(3,histo_vector(24)),_rawTMatrix(3,histo_vector(24)),
						_meanYMatrix(3,mean_vector(24)),_meanTMatrix(3,mean_vector(24)),
						_corrMatrix(3,corr_vector(24,std::make_pair(0,0))), _debug(true),
						_hitsTree("HitsTree","Tree with E3hits"),_rawHitsTree("RawHitsTree","Tree with E3RawHits")
{

}

E3Calib::E3Calib(bool debug):_YTrend(3,TGraph(24)),_TTrend(3,TGraph(24)),_rawYMatrix(3,histo_vector(24)),_rawTMatrix(3,histo_vector(24)),
							_meanYMatrix(3,mean_vector(24)),_meanTMatrix(3,mean_vector(24)),
							_corrMatrix(3,corr_vector(24,std::make_pair(0,0))),_debug(debug),
						_hitsTree("HitsTree","Tree with E3hits"),_rawHitsTree("RawHitsTree","Tree with E3RawHits")
{
}


E3Calib::~E3Calib(void)
{
}

void E3Calib::init()
{
	for (int chIdx=0;chIdx<_rawYMatrix.size();chIdx++)
	{
		_YTrend[chIdx].SetNameTitle((Form("yTrendCh_%d",chIdx)),Form("y Trend Chamber_%d",chIdx));
		_TTrend[chIdx].SetNameTitle((Form("tTrendCh_%d",chIdx)),Form("time Trend Chamber_%d",chIdx));
		for (int strIdx=0;strIdx<_rawYMatrix.at(0).size();strIdx++)
		{
			_rawYMatrix[chIdx][strIdx].Reset();
			_rawTMatrix[chIdx][strIdx].Reset();
			_rawYMatrix[chIdx][strIdx].SetNameTitle(Form("yValueCh_%d_Str_%d",chIdx,strIdx),Form("yValueCh_%d_Str_%d",chIdx,strIdx));
			_rawYMatrix[chIdx][strIdx].SetBins(100,-200,200);
			_rawTMatrix[chIdx][strIdx].SetNameTitle(Form("tValueCh_%d_Str_%d",chIdx,strIdx),Form("tValueCh_%d_Str_%d",chIdx,strIdx));
			_rawTMatrix[chIdx][strIdx].SetBins(250,0,500);
		}
	}

	//initTree

	 _hitsTree.Branch("eventNumber",&_hits_en   );
     _hitsTree.Branch("x"			,&_hits_x    );
     _hitsTree.Branch("y"			,&_hits_y    );
     _hitsTree.Branch("z"			,&_hits_z    );
     _hitsTree.Branch("THit"		,&_hits_THit );
     _hitsTree.Branch("TOT_l"		,&_hits_TOT_l);
     _hitsTree.Branch("TOT_r"		,&_hits_TOT_l);
	 
	 _rawHitsTree.Branch("eventNumber",&_hits_en);
	 _rawHitsTree.Branch("plane",&_rawHit_plane);
	 _rawHitsTree.Branch("strip",&_rawHit_strip);
	 _rawHitsTree.Branch("time",&_rawHit_time);
	 _rawHitsTree.Branch("side",&_rawHit_side);
	 _rawHitsTree.Branch("edge",&_rawHit_edge);
}

void E3Calib::computeCorrections()
{	
	std::cout<<"Computing corrections..."<< std::endl;
	double delta_time,hit_time,y_offset,strip_ps_offset;
	UInt_16b valid_strips=0;

	for (int chIdx=0;chIdx<_rawYMatrix.size();chIdx++) //chambers loop
	{
		//std::cout<<"correting chamber "<< chIdx<<std::endl;
		//compute mean hit arrival time
		hit_time=0.0;
		valid_strips=0;
		for (int strIdx=0;strIdx<_rawYMatrix.at(0).size();strIdx++)
		{
			if (_meanTMatrix[chIdx][strIdx]>0)
			{
				hit_time+=_meanTMatrix[chIdx][strIdx];//ps
				valid_strips++;
			}
		}
		hit_time/=valid_strips;
		//std::cout<<"mean hit time "<< hit_time<<std::endl;

		//adjust strip offset		
		for (int strIdx=0;strIdx<_rawYMatrix.at(0).size();strIdx++)
		{
			delta_time=(hit_time-_meanTMatrix[chIdx][strIdx])*1000.0;  //ps
			_corrMatrix[chIdx][strIdx].first=delta_time;   //hit time = (Tleft+Tright)/2
			_corrMatrix[chIdx][strIdx].second=delta_time;
			
			//std::cout<<"strip "<<strIdx<<" time correction: "<< delta_time<<std::endl;

			y_offset=_meanYMatrix[chIdx][strIdx];		//should be centered at 0.0
			//std::cout<<"strip "<<strIdx<<" y cm offset: "<< y_offset<<std::endl;
			strip_ps_offset=y_offset*2.0/PROP_SPEED*1000.0; //mean ps strip offset 
			//std::cout<<"strip "<<strIdx<<" y ps offset: "<< strip_ps_offset<<std::endl;
			
			_corrMatrix[chIdx][strIdx].first+=strip_ps_offset/2.0;   //negative side
			_corrMatrix[chIdx][strIdx].second-=strip_ps_offset/2.0;	//positive side
			//std::cout<<"strip "<<strIdx<<" negative side correction: "<< _corrMatrix[chIdx][strIdx].first<<std::endl;
			//std::cout<<"strip "<<strIdx<<" positive side correction: "<< _corrMatrix[chIdx][strIdx].second<<std::endl;
		}

	}
}

void E3Calib::fill()
{
	
	_hits_en   = getEvtNum() ;
	
	for (int chIdx=0;chIdx<_rawYMatrix.size();chIdx++)
	{
		E3HitVec hitVec=getHits(chIdx);
		for (int hitIdx=0;hitIdx<hitVec.size();hitIdx++)
		{
			_rawYMatrix[chIdx][hitVec[hitIdx].channel()].Fill(hitVec[hitIdx].y());
			_rawTMatrix[chIdx][hitVec[hitIdx].channel()].Fill(hitVec[hitIdx].hitTime());
			if(_debug)
			{
				_hits_y    = hitVec[hitIdx].y() ; 
				_hits_x    = hitVec[hitIdx].x() ;
				_hits_z    = hitVec[hitIdx].z() ;
				_hits_THit = hitVec[hitIdx].hitTime() ;
				_hits_TOT_l=hitVec[hitIdx].tot(0);
				_hits_TOT_l=hitVec[hitIdx].tot(1);

				
				_hitsTree.Fill();
			}
		}
	}

	//retrieve rawData
	if (_debug)
	{
		E3StripDataVecIter stripData;
		E3RawDataVecIter posEdge, negEdge;
		E3RawDataVec posVec, negVec;
		
		// Loop over the telescope planes...

		for (UInt_16b plane = 0; plane < 3; plane++) 
		{
			// Loop over the full strip data in the plane...
			for (stripData = m_stripDataVec[plane].begin();
			     stripData != m_stripDataVec[plane].end(); stripData++) 
			{
				_rawHit_plane=stripData->plane();
				_rawHit_strip=stripData->channel();
				// Double loop over the edges on the two plane end for the strip data.
				posVec = stripData->posEdgeDigiVec();
				negVec = stripData->negEdgeDigiVec();
				for (posEdge = posVec.begin(); posEdge != posVec.end(); posEdge++)
				{
					_rawHit_side=KSideLeft;
					_rawHit_time=posEdge->getPs();
					if (posEdge->isRisingEdge()) _rawHit_edge=KEdgeRise;
					else _rawHit_edge=KEdgeFall;
					_rawHitsTree.Fill();
				}
			    for (negEdge = negVec.begin(); negEdge != negVec.end(); negEdge++)
				{
					_rawHit_side=KSideRight;
					_rawHit_time=negEdge->getPs();
					if (negEdge->isRisingEdge()) _rawHit_edge=KEdgeRise;
					else _rawHit_edge=KEdgeFall;
					_rawHitsTree.Fill();
				}
			}
		}
	}
	
}


void E3Calib::getMean()
{
	for (int chIdx=0;chIdx<_rawYMatrix.size();chIdx++)
		for (int strIdx=0;strIdx<_rawYMatrix.at(0).size();strIdx++)
		{
			if (_rawYMatrix[chIdx][strIdx].GetEntries() > 100)
			{

				_rawTMatrix[chIdx][strIdx].Fit("gaus","Q");
				_meanYMatrix[chIdx][strIdx] = _rawYMatrix[chIdx][strIdx].GetMean();
				_meanTMatrix[chIdx][strIdx] = _rawTMatrix[chIdx][strIdx].GetFunction("gaus")->GetParameter(1);
				
				_YTrend[chIdx].SetPoint(strIdx,strIdx,_rawYMatrix[chIdx][strIdx].GetMean());
				_TTrend[chIdx].SetPoint(strIdx,strIdx,_rawTMatrix[chIdx][strIdx].GetFunction("gaus")->GetParameter(1));
			}
			else
			{
				_meanYMatrix[chIdx][strIdx] = 0.0;
				_meanTMatrix[chIdx][strIdx] = 0.0;
				_YTrend[chIdx].SetPoint(strIdx,strIdx,0.0);
				_TTrend[chIdx].SetPoint(strIdx,strIdx,0.0);
			}
		}
}



corr_matrix E3Calib::runCalibration(std::string Source,std::string OutDir,bool debug)
{

	init();

	_sourceStream.open(Source.c_str(),std::ios::binary);
	if(!_sourceStream.good()) 
	{

		std::cout<<"Unable to open input files...calibration aborted"<<std::endl;
		return _corrMatrix;
	}

	//get file size
    _sourceStream.seekg (0, _sourceStream.end);
	UInt_32b FileLength = _sourceStream.tellg();
    _sourceStream.seekg (0, _sourceStream.beg);
	
	//read Header
	_sourceStream.read((char*)&_headerStruct, sizeof(_headerStruct));  

	if (_headerStruct.Head_begin != 0xfbfbfbfb)
	{
		std::cout<< "Unknown file format..aborting"<<std::endl;
		return _corrMatrix;
	}


	
	//read Architecture
	_sourceStream.read((char*)&_archStruct, sizeof(_archStruct));

	//read GPS
	_sourceStream.read((char*)&_gpsStruct, sizeof(_gpsStruct)); 
	//set and print Gps info
	setGpsStruct(_gpsStruct);

	//read WS
	_sourceStream.read((char*)&_wsStruct, sizeof(_wsStruct)); 
	//set and print Gps info
	

	//set event gps timestamp
	setGpsTimestamp(getGpsE3Timestamp());

	if(createOutFile(OutDir)) 
	{

		std::cout<<"Unable to open all output files...calibration aborted"<<std::endl;
		return _corrMatrix;
	}
	std::cout<<"Calibrating..."<<std::endl;

	setNinoMap(_archStruct.NINO_map);
	
	std::cout<<"Skanning events....."<< std::endl;
	while (_sourceStream.tellg()<FileLength)
	{
		E3RecoEvent::clear();
		if(getEvent()==1)
		{
			std::cout<<"Event stream: unexpected fail to read file"<<std::endl;
			break;
		}
		
		if(unpack()==0)
		{
			
			findHits();
			fill();
			
		}
	}

	getMean();
	computeCorrections();
	closeOutFile();
	_sourceStream.close();

	
	std::cout<<"Calibration completed!"<<std::endl;

	return _corrMatrix;


}

void E3Calib::closeOutFile()
{
	if (_debug)
	{
		for (int chIdx=0;chIdx<_rawYMatrix.size();chIdx++)
		{
			_YTrend[chIdx].Write();
			_TTrend[chIdx].Write();
			for (int strIdx=0;strIdx<_rawYMatrix.at(0).size();strIdx++)
			{
				_rawYMatrix[chIdx][strIdx].Write();
				_rawTMatrix[chIdx][strIdx].Write();	
			}
		}
		_hitsTree.Write();
		_rawHitsTree.Write();
		_rootFile->Close();
	}
}

StatusCode E3Calib::createOutFile(std::string OutDir)
{	
	StatusCode OutputOpening=SUCCESS;	
	std::string fileName;

	//fileName=OutDir;
	//	fileName.append(_headerStruct.hRunName);	
	//	fileName.append("_cal.txt");
	//OutputOpening=_calFile.open(fileName);
	//if(OutputOpening==FAILURE) return OutputOpening;
	if (_debug)
	{

		fileName.clear();
		fileName=OutDir;
		fileName.append(_headerStruct.name);	
		fileName.append("_cde.root");
		_rootFile=new TFile(fileName.c_str(),"RECREATE");		
		if(!(_rootFile->IsOpen())) 
		{
			std::cout << "Unable to open root calibration debug file"<< std::endl;
			return FAILURE;
		}
		
		std::cout << "Debug file created: "<<fileName<< std::endl;
	}

	return OutputOpening;
}

UInt_16b E3Calib::getEvent()
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