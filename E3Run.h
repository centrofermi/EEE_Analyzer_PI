#ifndef BOSS__E3RUN__LIBGUARD
#define BOSS__E3RUN__LIBGUARD

class E3Run
{


private:

	//in file
	std::ifstream _sourceStream;

	//out file
	E3OutFileOUT  _outFile;
	E3OutFileSUM  _sumFile2;
	E3OutFileTIM  _timFile;
	E3OutFile2TT  _2ttFile;


	std::ofstream _sumFile;

	E3Gps	_gps;
	E3RecoEvent _event;

	//run header info
	
	UInt_32b	_hH,_hT;        //header header and trailer
	UInt_16b	_hVersion;		//DAQ Version
	UInt_64b	_hStartTime;    //DAQ PC unix timestamp of run start
	UInt_8b		_hTrgMask;		//trigger mask
	UInt_16b	_hRunNameL;		//run name byte lenght
	char		_hRunName[128];	//run name
	UInt_8b		_hMachineID;	//identifier of the telescope ID
	UInt_32b	_hRunNumber;	//proggressive run number for the telescope
	UInt_32b	_hNinoMap;		//nino map

	//run sum
	UInt_32b _analyzed;										//events correctly analyzed

	std::vector<std::vector<UInt_32b> >  _gHitMult;	//hits multiplicity for each chamber
	std::vector<UInt_32b>  _gSumHitMult;				//hits multiplicity for each event
	UInt_32b	_gLowHitMult;							//events with AT LEAST one empty chamber
	UInt_32b	_gMediumHitMult;						//events with 1 or 2 hit/chamber
	UInt_32b	_gHighHitMult;							//events with at least one chamber with hit multiplicity > 2

	std::vector<std::vector<UInt_32b> >  _gClusterMult;		//cluster multiplicity for each chamber
	std::vector<UInt_32b>  _gSumClusterMult;				//cluster multiplicity for each event
	UInt_32b	_gLowClusterMult;							//events with AT LEAST one empty chamber
	UInt_32b	_gMediumClusterMult;						//events with 1 or 2 cluster/chamber
	UInt_32b	_gHighClusterMult;							//events with at least one chamber with cluster multiplicity > 2
	
	StatusCode createOutFile(std::string OutDir);
	UInt_16b getEvent();
	void getMultiplicity();


public:
	E3Run(void);
	~E3Run(void);

	
	void analyzeRun(std::string Source,std::string OutDir);



	//call to gps class
	inline UInt_64b					getGpsE3Timestamp()							{return _gps.getGpsE3Timestamp();};
	inline t_gps					getGpsStruct()								{return _gps.getGpsStruct();};
	inline void						setGpsStruct(t_gps gps_s)					{_gps.setGpsStruct(gps_s);};
	inline std::ostream&			writeGpsInfo(std::ostream& os)				{return _gps.writeGpsInfo(os);};


	//write info
	std::ostream&	writeEventTim(std::ostream& os=std::cout);
	std::ostream&	writeRunSum(std::ostream& os=std::cout);
	std::ostream&	writeHeaderInfo(std::ostream& os=std::cout);
};

#endif